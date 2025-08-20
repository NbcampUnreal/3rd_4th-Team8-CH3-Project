// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "Items/ConsumableItems/HealingItemAttributeSet.h"
#include "GameplayEffectExecutionCalculation.h"
#include "HealingExecution.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UHealingExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
    UHealingExecution();

    virtual void Execute_Implementation(
        const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OutExecutionOutput
    ) const override;
};
