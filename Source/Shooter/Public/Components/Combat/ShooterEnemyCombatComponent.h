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

public:
	virtual void OnHitTargetActor(AActor* HitActor) override;

private:
	void TriggerGameplayEvent(const FGameplayTag EventTag, const FGameplayEventData& EventData);
};
