// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ShooterAttributeSet.h"

UShooterAttributeSet::UShooterAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
	InitAttackRange(1.f);
}

void UShooterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// TODO: ui 변경에 대한 로직 작성 필요
}
