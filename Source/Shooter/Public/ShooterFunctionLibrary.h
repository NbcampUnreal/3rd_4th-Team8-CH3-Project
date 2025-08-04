// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShooterFunctionLibrary.generated.h"

struct FGameplayTag;

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Shooter|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

private:
	static FGameplayTag DetermineHitReactionTag(const float& OutAngleDifference);
};
