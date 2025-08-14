// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "ShooterUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChangedDelegate, float, NewAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemCooldownStartDelegate, FName, UseItemName, float, CooldwonDuration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShooterDeadDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartZoomDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndZoomDelegate);
/**
 *
/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChangedDelegate  OnCurrentAmmoChanged;

	UPROPERTY(BlueprintAssignable)
	FOnItemCooldownStartDelegate  OnItemCooldownStart;

	
public:
	UPROPERTY(BlueprintAssignable)
	FOnStartZoomDelegate  OnStartZoom;

	UPROPERTY(BlueprintAssignable)
	FOnEndZoomDelegate  OnEndZoom;

	UPROPERTY(BlueprintAssignable)
	FOnShooterDeadDelegate OnShooterDead;

	void HandleCurrentAmmoChanged(float NewAmmo);
	UFUNCTION(BlueprintCallable)
	void HandleStartCooldown(FName UseItemName, float CooldownDuration);
	UFUNCTION(BlueprintCallable)
	void HandleShooterDead();
};
