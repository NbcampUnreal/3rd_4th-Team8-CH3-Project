// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterBaseCharacter.h"
#include "GameplayEffectTypes.h"
#include "ShooterEnemyCharacter.generated.h"


class UDataAsset_InputConfig;
class AAIController;
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

	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnHealthChanged(float OldValue, float NewValue);
};
