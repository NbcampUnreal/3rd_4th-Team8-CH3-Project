// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpDatas/DataAsset_ShooterStartUpData.h"
#include "AbilitySystem/Abilities/ShooterPlayerGameplayAbility.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Shooter/ShooterDebugHelper.h"

void UDataAsset_ShooterStartUpData::GiveToAbilitySystemComponent(
	UShooterAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel
)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	for (const FShooterAbilitySet& AbilitySet : ShooterStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		// 	const FString WeaponString = FString::Printf(
		// TEXT("무기이름: %s, 등록된 태그: %s"), *InWeaponToResister->GetName(), *InWeaponTagToResister.ToString());
		// 	Debug::Print(WeaponString);

		const FString InputTagString =
			FString::Printf(TEXT("AbilitySet.InputTag: %s"), *AbilitySet.InputTag.ToString());
		//

		Debug::Print(InputTagString);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
