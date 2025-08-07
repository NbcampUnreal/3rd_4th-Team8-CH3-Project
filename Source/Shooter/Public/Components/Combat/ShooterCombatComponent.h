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
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractingActor) override;

	UFUNCTION(BlueprintCallable, Category = "Shooter|Combat")
	AShooterPlayerWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AShooterPlayerWeapon* GetShooterCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Shooter|Combat")
	float GetShooterCurrentEquippedWeaponDamageAtLevel(float InLevel) const;
};
