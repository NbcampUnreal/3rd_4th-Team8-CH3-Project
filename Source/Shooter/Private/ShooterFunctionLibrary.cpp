// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "ShooterGamePlayTag.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

UShooterAbilitySystemComponent* UShooterFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UShooterAbilitySystemComponent>(
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor)
	);
}

void UShooterFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UShooterAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

FGameplayTag UShooterFunctionLibrary::ComputeHitReactDirectionTag(
	AActor* InAttacker,
	AActor* InVictim,
	float& OutAngleDifference
)
{
	// InAttacker와 InVictim이 nullptr이 아니어야 함 (디버깅 중 예외 처리)
	check(InAttacker && InVictim);

	// 피격자의 정면 방향 벡터를 가져옴
	const FVector VictimForward = InVictim->GetActorForwardVector();

	// 피격자 → 공격자 방향 벡터를 정규화하여 구함
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).
		GetSafeNormal();

	// 두 벡터의 내적 결과 (코사인 값)를 구함
	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);

	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);
	// acos 결과를 도(degree) 단위로 변환하여 각도 차이 저장KismetMathLibrary::DegAcos(DotResult);

	// 좌우 방향 판별을 위한 외적 계산
	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	// 외적 결과의 Z 값이 음수이면 오른쪽에서 공격 -> 각도 부호를 음수로 바꿈
	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}
	return DetermineHitReactionTag(OutAngleDifference);
}

UPawnCombatComponent* UShooterFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EShooterValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	OutValidType = CombatComponent ? EShooterValidType::EWT_Valid : EShooterValidType::EWT_Invalid;
	return CombatComponent;
}

UPawnCombatComponent* UShooterFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (const IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

void UShooterFunctionLibrary::BP_DoesActorHaveTag(
	AActor* InActor,
	FGameplayTag TagToCheck,
	EShooterConfirmType& OutConfirmType
)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck)
		                 ? EShooterConfirmType::ESC_Yes
		                 : EShooterConfirmType::ESC_No;
}

bool UShooterFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UShooterAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

/**
 * 두 Pawn 간의 팀을 비교하여 적대 관계인지 여부를 판단.
 * 
 * @param QueryPawn 판단의 기준이 되는 Pawn (예: AI 또는 플레이어 본인)
 * @param TargetPawn 적대 여부를 판단할 대상 Pawn
 * @return 두 Pawn이 서로 다른 TeamId를 가지고 있으면 true (적대 관계), 그렇지 않으면 false
 *
 * @note 두 Pawn의 컨트롤러는 IGenericTeamAgentInterface를 구현하고 있어야 하며,
 *       구현되어 있지 않거나 null일 경우 false를 반환
 */
bool UShooterFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* GenericTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (GenericTeamAgent && TargetTeamAgent)
	{
		// 팀 ID가 다르면 적대 관계로 간주하여 true 반환
		return GenericTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	// 팀 인터페이스를 구현하지 않은 경우 적대 관계로 간주하지 않음
	return false;
}

bool UShooterFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(
	AActor* InInstigator,
	AActor* InTargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle
)
{
	UShooterAbilitySystemComponent* SourceASC = NativeGetWarriorASCFromActor(InInstigator);
	UShooterAbilitySystemComponent* TargetASC = NativeGetWarriorASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

FGameplayTag UShooterFunctionLibrary::DetermineHitReactionTag(const float& OutAngleDifference)
{
	// -45 ~ 45도 사이면 정면
	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return ShooterGamePlayTags::Shared_Status_HitReact_Front;
	}
	// -135 ~ -45도 사이면 왼쪽
	if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return ShooterGamePlayTags::Shared_Status_HitReact_Left;
	}
	// - 135보다 작거나 135보다 크면 오른쪽
	if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return ShooterGamePlayTags::Shared_Status_HitReact_Back;
	}
	// 45 ~ 135도 사이면 뒤
	if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return ShooterGamePlayTags::Shared_Status_HitReact_Right;
	}
	return ShooterGamePlayTags::Shared_Status_HitReact_Front;
}
