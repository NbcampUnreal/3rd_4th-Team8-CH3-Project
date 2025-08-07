// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpDatas/DataAsset_StartUpDataBase.h"
#include "ShooterTypes/ShooterStructTypes.h"
#include "DataAsset_ShooterStartUpData.generated.h"

// struct FShooterAbilitySet;
/**
 * 
 */
UCLASS()
class SHOOTER_API UDataAsset_ShooterStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void
	GiveToAbilitySystemComponent(UShooterAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FShooterAbilitySet> ShooterStartUpAbilitySets;
};
