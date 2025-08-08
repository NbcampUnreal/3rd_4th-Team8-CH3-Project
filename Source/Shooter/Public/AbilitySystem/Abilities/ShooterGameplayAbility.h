// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ShooterTypes/ShooterEnumTypes.h"
#include "ShooterGameplayAbility.generated.h"


class UPawnCombatComponent;
class UShooterAbilitySystemComponent;

UENUM(BlueprintType)
enum class EShooterAbilityActivationPolicy : uint8
{
	/* 입력 또는 게임플레이 이벤트를통해 트리거 될때 */
	EWA_OnTriggered,

	/* 대상에게 주어지면 바로 능력 발동 */
	EWA_OnGiven
};

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Shooter|Ability")
	EShooterAbilityActivationPolicy AbilityActivationPolicy = EShooterAbilityActivationPolicy::EWA_OnTriggered;

	// ~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
		bool bWasCancelled
	) override;
	// ~ End UGameplayAbility Interface.

	UFUNCTION(BlueprintPure, Category = "Shooter|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(
		AActor* TargetActor,
		const FGameplayEffectSpecHandle& InSpecHandle
	);

	UFUNCTION(BlueprintPure, Category = "Shooter|Ability")
	UShooterAbilitySystemComponent* GetShooterAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(
		BlueprintCallable,
		Category = "Shooter|Ability",
		meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType")
	)
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(
		AActor* TargetActor,
		const FGameplayEffectSpecHandle& InSpecHandle,
		EShooterSuccessType& OutSuccessType
	);
};
