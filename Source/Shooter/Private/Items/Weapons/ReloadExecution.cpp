// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ReloadExecution.h"
#include "ShooterGamePlayTag.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"

UReloadExecution::UReloadExecution()
{
}

void UReloadExecution::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    // SetByCaller로 전달된 값 가져오기
    float ReloadAmount = Spec.GetSetByCallerMagnitude(ShooterGamePlayTags::Shared_Data_ReloadAmount, true);

    //SetByCaller로 설정된 ReloadAmount를 CurrentAmmo에 더하기
    FGameplayModifierEvaluatedData EvalData(
        UWeaponAttributeSet::GetCurrentAmmoAttribute(),
        EGameplayModOp::Additive,
        ReloadAmount);

    OutExecutionOutput.AddOutputModifier(EvalData);
}
