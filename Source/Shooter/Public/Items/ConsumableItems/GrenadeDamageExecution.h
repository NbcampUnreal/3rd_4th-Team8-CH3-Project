// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GrenadeDamageExecution.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UGrenadeDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
    UGrenadeDamageExecution();

    virtual void Execute_Implementation(
        const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OutExecutionOutput
    ) const override;
};
