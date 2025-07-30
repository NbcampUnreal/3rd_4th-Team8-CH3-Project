// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "WeaponAttributeSet.h"
#include "ConsumeAmmoExecution.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UConsumeAmmoExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
    UConsumeAmmoExecution();

    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
