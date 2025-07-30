// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ShooterAttributeSet.h"
#include "Characters/ShooterBaseCharacter.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UShooterAttributeSet::UShooterAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UShooterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
