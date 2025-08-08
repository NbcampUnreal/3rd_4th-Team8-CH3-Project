// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "WeaponAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UWeaponAttributeSet : public UShooterAttributeSet
{
	GENERATED_BODY()

public:
    UWeaponAttributeSet();

    void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    // 최대 탄약 수
    UPROPERTY(BlueprintReadOnly, Category = "Weapon")
    FGameplayAttributeData MaxAmmo;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxAmmo)

    // 현재 탄약 수
    UPROPERTY(BlueprintReadOnly, Category = "Weapon")
    FGameplayAttributeData CurrentAmmo;
    ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, CurrentAmmo)
};
