// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ShooterAbilitySystemComponent.h"

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
