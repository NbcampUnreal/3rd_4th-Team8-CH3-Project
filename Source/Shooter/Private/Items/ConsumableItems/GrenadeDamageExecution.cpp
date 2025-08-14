// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItems/GrenadeDamageExecution.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "Items/ConsumableItems/GrenadeAttributeSet.h"

UGrenadeDamageExecution::UGrenadeDamageExecution()
{
}

void UGrenadeDamageExecution::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    const FGameplayEffectContextHandle& ContextHandle = Spec.GetContext();

    AActor* InstigatorActor = ContextHandle.GetInstigator();
    if (!InstigatorActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("[GrenadeExec] No InstigatorActor"));
        return;
    }

    UShooterAbilitySystemComponent* ActivatorASC = InstigatorActor->FindComponentByClass<UShooterAbilitySystemComponent>();
    if (!ActivatorASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[GrenadeExec] No ActivatorASC"));
        return;
    }

    const UGrenadeAttributeSet* GrenadeAttrSet = ActivatorASC->GetSet<UGrenadeAttributeSet>();
    if (!GrenadeAttrSet)
    {
        UE_LOG(LogTemp, Warning, TEXT("[GrenadeExec] No GrenadeAttributeSet"));
        return;
    }

    float GrenadeDamage = GrenadeAttrSet->GetGrenadeDamageAmount();
    UE_LOG(LogTemp, Warning, TEXT("[GrenadeExec] GrenadeDamageAmount from Instigator: %f"), GrenadeDamage);

    // Target ASC 가져오기
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
    if (!TargetASC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[GrenadeExec] No Target ASC"));
        return;
    }

    // DamageTaken Attribute로 데미지 적용
    FGameplayModifierEvaluatedData EvalData(
        UShooterAttributeSet::GetDamageTakenAttribute(),  // 기존 CurrentHealth 대신 DamageTaken
        EGameplayModOp::Additive,
        GrenadeDamage
    );

    OutExecutionOutput.AddOutputModifier(EvalData);

    // 디버그: 적용 전 Target CurrentHealth
    if (const UShooterAttributeSet* TargetAttr = TargetASC->GetSet<UShooterAttributeSet>())
    {
        UE_LOG(LogTemp, Warning, TEXT("[GrenadeExec] Target CurrentHealth BEFORE: %f"), TargetAttr->GetCurrentHealth());
    }
}

	