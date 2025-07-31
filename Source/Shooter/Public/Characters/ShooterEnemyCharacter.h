// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterBaseCharacter.h"
#include "GameplayEffectTypes.h"
#include "ShooterEnemyCharacter.generated.h"


class UDataAsset_InputConfig;
/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterEnemyCharacter : public AShooterBaseCharacter
{
	GENERATED_BODY()

public:
	AShooterEnemyCharacter();

protected:
	virtual void BeginPlay() override;

	UDataAsset_InputConfig* InputConfigDataAsset;

	FDelegateHandle HealthChangedDelegateHandle;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	void AddCharacterAbilities();
	void InitializeAttributes();
	void AddStartupEffects();

};
