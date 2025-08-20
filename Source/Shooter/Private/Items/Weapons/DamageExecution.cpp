// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/DamageExecution.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
UDamageExecution::UDamageExecution()
{

}

void UDamageExecution::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
    if (!TargetASC) return;

    const UShooterAttributeSet* TargetAttrSet = TargetASC->GetSet<UShooterAttributeSet>();
    if (!TargetAttrSet) return;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    const FGameplayEffectContextHandle& ContextHandle = Spec.GetContext();

 	AActor* InstigatorActor = ContextHandle.GetInstigator();
	if (!InstigatorActor) return;
	
    UAbilitySystemComponent* ActivatorASC = InstigatorActor->FindComponentByClass<UAbilitySystemComponent>();
	if (!ActivatorASC) return;

    const UShooterAttributeSet* ActivatorAttrSet = ActivatorASC->GetSet<UShooterAttributeSet>();
    if (!ActivatorAttrSet) return;

    float TargetHealth = TargetAttrSet->GetCurrentHealth();
    float ActivatorAttackPower = ActivatorAttrSet->GetAttackPower();

    // 맞은 ShooterAttributeSet의 Current Health 변수 어빌리티 사용자의 AttackPower만큼 Additive(더하기)
    FGameplayModifierEvaluatedData EvalData(
        UShooterAttributeSet::GetCurrentHealthAttribute(),
        EGameplayModOp::Additive,
        -ActivatorAttackPower
    );

    OutExecutionOutput.AddOutputModifier(EvalData);
}


