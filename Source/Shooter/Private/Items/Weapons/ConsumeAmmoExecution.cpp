// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ConsumeAmmoExecution.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"

UConsumeAmmoExecution::UConsumeAmmoExecution()
{
}

void UConsumeAmmoExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
    if (!TargetASC)
    {
        return;
    }

    const UWeaponAttributeSet* WeaponAttrSet = TargetASC->GetSet<UWeaponAttributeSet>();
    if (!WeaponAttrSet)
    {
        return;
    }

    // WeaponAttributeSet의 CurrentAmmo 변수 -1 만큼 Additive(더하기)
    FGameplayModifierEvaluatedData EvalData(
        UWeaponAttributeSet::GetCurrentAmmoAttribute(),
        EGameplayModOp::Additive,
        -1);

    OutExecutionOutput.AddOutputModifier(EvalData);
}
