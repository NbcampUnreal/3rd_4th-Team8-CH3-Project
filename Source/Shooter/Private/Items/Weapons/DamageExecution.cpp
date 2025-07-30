// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/DamageExecution.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
UDamageExecution::UDamageExecution()
{

}

void UDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
    if (!TargetASC)
    {
        return;
    }
    const UShooterAttributeSet* TargetAttrSet = TargetASC->GetSet<UShooterAttributeSet>();
    if (!TargetAttrSet)
    {
        return;
    }

    UAbilitySystemComponent* ActivatorASC = nullptr;
    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    const FGameplayEffectContextHandle& ContextHandle = Spec.GetContext();

    AActor* InstigatorActor = ContextHandle.GetInstigator();
    if (InstigatorActor)
    {
        ActivatorASC = InstigatorActor->FindComponentByClass<UAbilitySystemComponent>();
        if (!ActivatorASC)
        {
            return;
        }
    }
    else
    {
        return;
    }
    const UShooterAttributeSet* ActivatorAttrSet = ActivatorASC->GetSet<UShooterAttributeSet>();
    if (!ActivatorAttrSet)
    {
        return;
    }

    float TargetHealth = TargetAttrSet->GetCurrentHealth();
    float ActivatorAttackPower = ActivatorAttrSet->GetAttackPower();

    FGameplayModifierEvaluatedData EvalData(
        UShooterAttributeSet::GetCurrentHealthAttribute(),
        EGameplayModOp::Additive,
        -ActivatorAttackPower
    );

    OutExecutionOutput.AddOutputModifier(EvalData);
}


