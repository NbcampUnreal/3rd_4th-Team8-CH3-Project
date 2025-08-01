// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "HealingItemAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UHealingItemAttributeSet : public UShooterAttributeSet
{
	GENERATED_BODY()
public:
    UHealingItemAttributeSet();

    // 힐 아이템 회복량
    UPROPERTY(BlueprintReadOnly, Category = "Weapon")
    FGameplayAttributeData HealAmount;
    ATTRIBUTE_ACCESSORS(UHealingItemAttributeSet, HealAmount)

};
