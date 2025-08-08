// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItems/HealingExecution.h"

UHealingExecution::UHealingExecution()
{
}

void UHealingExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!TargetASC)
	{
		return;
	}

	const UHealingItemAttributeSet* HealAttrSet = TargetASC->GetSet<UHealingItemAttributeSet>();
	if (!HealAttrSet)
	{
		return;
	}

	float HealAmount = HealAttrSet->GetHealAmount();

	// 맞은 ShooterAttributeSet의 Current Health 변수 만큼 Additive(더하기)
	FGameplayModifierEvaluatedData EvalData(
		UShooterAttributeSet::GetCurrentHealthAttribute(),
		EGameplayModOp::Additive,
		HealAmount
	);

	OutExecutionOutput.AddOutputModifier(EvalData);
}
