// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ReloadExecution.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"

UReloadExecution::UReloadExecution()
{
}

void UReloadExecution::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
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

    // WeaponAttributeSet의 CurrentAmmo 변수 MaxAmmo로 Override(덮어쓰기)
    FGameplayModifierEvaluatedData EvalData(
        UWeaponAttributeSet::GetCurrentAmmoAttribute(),
        EGameplayModOp::Override,
        NewAmmo);

    OutExecutionOutput.AddOutputModifier(EvalData);
}
