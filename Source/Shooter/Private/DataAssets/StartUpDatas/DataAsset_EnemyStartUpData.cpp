// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpDatas/DataAsset_EnemyStartUpData.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ShooterEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UShooterAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyGameplayAbility.IsEmpty())
	{
		for(const TSubclassOf<UShooterEnemyGameplayAbility>& AbilityClass : EnemyGameplayAbility)
		{
			if (!AbilityClass) continue;
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
		
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
