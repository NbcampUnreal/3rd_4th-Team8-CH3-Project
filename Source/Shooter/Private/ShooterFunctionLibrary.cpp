// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "ShooterGamePlayTag.h"
#include "Kismet/KismetMathLibrary.h"

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
