// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ReloadExecution.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"

UReloadExecution::UReloadExecution()
{
}

void UReloadExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
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

    float MaxAmmo = WeaponAttrSet->GetMaxAmmo();
    float NewAmmo = MaxAmmo;

    // CurrentAmmo 어트리뷰트에 Override 모드로 변경 요청
    FGameplayModifierEvaluatedData EvalData(
        UWeaponAttributeSet::GetCurrentAmmoAttribute(),
        EGameplayModOp::Override,
        NewAmmo);

    OutExecutionOutput.AddOutputModifier(EvalData);
}
