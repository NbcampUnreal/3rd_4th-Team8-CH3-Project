// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "GrenadeAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UGrenadeAttributeSet : public UShooterAttributeSet
{
	GENERATED_BODY()
public:
    UGrenadeAttributeSet();

    // 힐 아이템 회복량
    UPROPERTY(BlueprintReadOnly, Category = "Item")
    FGameplayAttributeData GrenadeDamageAmount;
    ATTRIBUTE_ACCESSORS(UGrenadeAttributeSet, GrenadeDamageAmount)
};
