// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShooterTypes/ShooterEnumTypes.h"
#include "ShooterFunctionLibrary.generated.h"

struct FGameplayTag;
class UShooterAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UShooterAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Shooter|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintPure, Category = "Shooter|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(
		BlueprintCallable,
		Category = "Shooter|FunctionLibrary",
		meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType")
	)
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EShooterConfirmType& OutConfirmType);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintPure, Category = "Shooter|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Shooter|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(
		AActor* InInstigator,
		AActor* InTargetActor,
		const FGameplayEffectSpecHandle& InSpecHandle
	);

private:
	static FGameplayTag DetermineHitReactionTag(const float& OutAngleDifference);
};
