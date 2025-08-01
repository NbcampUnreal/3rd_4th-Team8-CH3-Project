// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UGameplayEffect;
class UShooterGameplayAbility;
class UShooterAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class SHOOTER_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UShooterAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

	int32 a;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UShooterGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UShooterGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<UShooterGameplayAbility>>& InAbilitiesToGive,
	                    UShooterAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
