// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpDatas/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"

/**
 * 지정된 능력 시스템 컴포넌트(ASC)에 게임플레이 능력 및 효과를 부여합니다.
 *
 * @param InASCToGive 능력을 부여받을 UShooterAbilitySystemComponent입니다.
 * @param ApplyLevel 부여된 능력 및 효과의 적용 레벨입니다.
 */
void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(
	UShooterAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel
)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectsClass : StartUpGameplayEffects)
		{
			if (!EffectsClass)
			{
				continue;
			}
			UGameplayEffect* EffectCDO = EffectsClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, InASCToGive->MakeEffectContext());
		}
	}
}

/**
 * 제공된 UShooterAbilitySystemComponent에 지정된 게임플레이 능력을 부여합니다.
 *
 * @param InAbilitiesToGive 부여할 UShooterGameplayAbility 클래스의 배열입니다.
 * @param InASCToGive 능력을 부여받을 UShooterAbilitySystemComponent입니다.
 * @param ApplyLevel 부여된 능력의 적용 레벨입니다.
 */
void UDataAsset_StartUpDataBase::GrantAbilities(
	const TArray<TSubclassOf<UShooterGameplayAbility>>& InAbilitiesToGive,
	UShooterAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel
)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	for (const TSubclassOf<UShooterGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
