// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "ShooterUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChangedDelegate, float, NewAmmo);


/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChangedDelegate  OnCurrentAmmoChanged;


public:
	void HandleCurrentAmmoChanged(float NewAmmo);
};
