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
		return;
	}

	UAbilitySystemComponent* ActivatorASC = InstigatorActor->FindComponentByClass<UAbilitySystemComponent>();
	if (!ActivatorASC)
	{
		return;
	}

	const UGrenadeAttributeSet* GrenadeAttrSet = ActivatorASC->GetSet<UGrenadeAttributeSet>();
	if (!GrenadeAttrSet)
	{
		return;
	}

	float GrenadeDamage = GrenadeAttrSet->GetGrenadeDamageAmount();

	FGameplayModifierEvaluatedData EvalData(
		UShooterAttributeSet::GetCurrentHealthAttribute(),
		EGameplayModOp::Additive,
		-GrenadeDamage
	);

	OutExecutionOutput.AddOutputModifier(EvalData);
}
	