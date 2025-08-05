// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "ShooterPlayerGameplayAbility.generated.h"

class UShooterCombatComponent;
class AShooterController;
class AShooterCharacter;
/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterPlayerGameplayAbility : public UShooterGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Shooter|Ability")
	AShooterCharacter* GetShooterCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Shooter|Ability")
	AShooterController* GetShooterControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Shooter|Ability")
	UShooterCombatComponent* GetShooterCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AShooterCharacter> CachedShooterCharacter;
	TWeakObjectPtr<AShooterController> CachedShooterController;
};
