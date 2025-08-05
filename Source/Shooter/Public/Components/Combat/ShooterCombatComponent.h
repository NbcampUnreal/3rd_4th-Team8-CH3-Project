// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "ShooterCombatComponent.generated.h"

class AShooterPlayerWeapon;
/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Shooter|Combat")
	AShooterPlayerWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Shooter|Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;
};
