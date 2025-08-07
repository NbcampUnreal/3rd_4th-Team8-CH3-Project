// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalculate/UGEExecCalculate_DamageTaken.h"

#include "ShooterGamePlayTag.h"
#include "AbilitySystem/ShooterAttributeSet.h"

struct FShooterDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FShooterDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UShooterAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UShooterAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UShooterAttributeSet, DamageTaken, Target, false);
	}
};

static FShooterDamageCapture& GetShooterDamageCapture()
{
	static FShooterDamageCapture WarriorDamageCapture;
	return WarriorDamageCapture;
}

UGEExecCalculate_DamageTaken::UGEExecCalculate_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetShooterDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetShooterDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetShooterDamageCapture().DamageTakenDef);
}

void UGEExecCalculate_DamageTaken::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
	// 데미지를 받을 대상의 어빌리티 시스템 컴포넌트 GET
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();

	if (TargetAbilitySystemComponent)
	{
		FGameplayTagContainer OwnedTags;
		TargetAbilitySystemComponent->GetOwnedGameplayTags(OwnedTags);

		// 태그들을 문자열로 출력
		for (const FGameplayTag& Tag : OwnedTags)
		{
			UE_LOG(LogTemp, Warning, TEXT("보유 중인 태그: %s"), *Tag.ToString());
		}
	}

	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetShooterDamageCapture().AttackPowerDef,
		EvaluateParameters,
		SourceAttackPower
	);

	float BaseDamage = 0.f;
	int32 UsedChargeAttackDamage = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitube : EffectSpec.SetByCallerTagMagnitudes)
	{
		const float MagnitudeValue = TagMagnitube.Value;
		if (TagMagnitube.Key.MatchesTagExact(ShooterGamePlayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = MagnitudeValue;
			// Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}
		if (TagMagnitube.Key.MatchesTagExact(ShooterGamePlayTags::Player_SetByCaller_AttackType_ChargeShoot))
		{
			UsedChargeAttackDamage = MagnitudeValue;
		}
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetShooterDamageCapture().DefensePowerDef,
		EvaluateParameters,
		TargetDefensePower
	);

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;

	if (FinalDamageDone > 0.f)
	{
		FGameplayModifierEvaluatedData ModifierEvaluatedData = FGameplayModifierEvaluatedData(
			GetShooterDamageCapture().DamageTakenProperty,
			EGameplayModOp::Override,
			FinalDamageDone
		);

		OutExecutionOutput.AddOutputModifier(ModifierEvaluatedData);
	}
}
