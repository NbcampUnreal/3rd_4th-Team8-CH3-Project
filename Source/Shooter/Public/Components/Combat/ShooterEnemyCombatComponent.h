// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "ShooterEnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

	// public, protected, private이 없으면 암묵적으로 "private" 화 됨
	void TriggerGameplayEvent(const FGameplayTag EventTag, const FGameplayEventData& EventData);
};
