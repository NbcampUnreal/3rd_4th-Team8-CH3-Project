// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "ShooterEnemyGameplayAbility.generated.h"

class AShooterEnemyCharacter;
class UShooterEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterEnemyGameplayAbility : public UShooterGameplayAbility
{
	GENERATED_BODY()


	UFUNCTION(BlueprintPure, Category = "Shooter|Ability", meta = (AllowPrivateAccess = "true"))
	AShooterEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Shooter|Ability", meta = (AllowPrivateAccess = "true"))
	UShooterEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	TWeakObjectPtr<AShooterEnemyCharacter> CachedShooterEnemyCharacter;
};
