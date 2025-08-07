// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ShooterPlayerGameplayAbility.h"
#include "Shooter/ShooterDebugHelper.h"

/**
 * 능력 활성화 입력이 감지되었을 때 호출되는 메소드입니다.
 * 주어진 입력 태그에 해당하는 능력을 검색하고 조건에 맞는 경우 활성화 시도합니다.
 *
 * @param InputTag 입력과 연관된 FGameplayTag입니다. 유효하지 않은 태그(Invalid)일 경우 메소드는 아무 작업도 수행하지 않습니다.
 */
void UShooterAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			continue;
		}
		UE_LOG(LogTemp, Warning, TEXT("MATCH FOUND! Activating Ability for InputTag: %s"), *InputTag.ToString());
		TryActivateAbility(AbilitySpec.Handle);
	}
}

/**
 * 능력 비활성화 입력이 감지되었을 때 호출되는 메소드입니다.
 * 주어진 입력 태그에 해당하는 활성화된 능력을 검색하고, 입력 태그와 일치하는 경우 비활성화를 시도합니다.
 *
 * @param InputTag 입력과 연관된 FGameplayTag입니다. 유효하지 않은 태그(Invalid)일 경우 메소드는 아무 작업도 수행하지 않습니다.
 */
void UShooterAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	// TODO:  || !InputTag.MatchesTag(ShooterGamePlayTags::InputTag_MustBeHeld) 추가 예정
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void UShooterAbilitySystemComponent::GrantShooterWeaponAbilities(
	const TArray<FShooterAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}
	for (const FShooterAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UShooterAbilitySystemComponent::RemoveGrantShooterWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesRemove)
{
	if (InSpecHandlesRemove.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	// 혹시모를 안전장치
	InSpecHandlesRemove.Empty();
}

bool UShooterAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	// 해당 태그와 일치하는 활성화 가능한 어빌리티들을 담을 배열
	TArray<FGameplayAbilitySpec*> FoundAbilitiesSpecs;

	// AbilityTagToActivate와 일치하는 어빌리티들을 검색하여 FoundAbilitiesSpecs에 채운다
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(
		AbilityTagToActivate.GetSingleTagContainer(), // 단일 태그 컨테이너로 변환
		FoundAbilitiesSpecs
	);

	// 조건: 태그에 해당하는 어빌리티가 하나라도 있다면
	if (!FoundAbilitiesSpecs.IsEmpty())
	{
		// 어빌리티가 여러 개일 수 있으므로, 무작위로 하나 선택
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitiesSpecs.Num() - 1);
		const FGameplayAbilitySpec* SpecToActivate = FoundAbilitiesSpecs[RandomAbilityIndex];

		// 무작위로 선택된 어빌리티가 null이 아닌지 확인
		check(SpecToActivate);

		// 이미 활성화된 어빌리티가 아니라면
		if (!SpecToActivate->IsActive())
		{
			// 해당 어빌리티를 활성화 시도하고 결과 반환
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}

	// 어빌리티를 찾지 못했거나 이미 활성화된 경우 false 반환
	return false;
}
