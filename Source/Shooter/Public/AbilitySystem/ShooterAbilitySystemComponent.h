// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ShooterTypes/ShooterStructTypes.h"
#include "ShooterAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "Shooter|Ability", meta = (ApplyLevel = "1"))
	void GrantShooterWeaponAbilities(
		const TArray<FShooterAbilitySet>& InDefaultWeaponAbilities,
		int32 ApplyLevel,
		TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles
	);

	UFUNCTION(BlueprintCallable, Category = "Shooter|Ability")
	void RemoveGrantShooterWeaponAbilities(
		UPARAM(ref)
		TArray<FGameplayAbilitySpecHandle>& InSpecHandlesRemove
	);

	UFUNCTION(BlueprintCallable, Category = "Shooter|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
};
