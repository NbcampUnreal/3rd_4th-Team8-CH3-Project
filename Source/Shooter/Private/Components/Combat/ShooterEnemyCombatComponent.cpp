// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/ShooterEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ShooterGamePlayTag.h"

void UShooterEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// 이미 겹친 액터(같은 프레임에서 중복 피격 방지)에 포함되어 있다면 리턴
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn(); // 공격자 설정
	EventData.Target = HitActor; // 피격 대상 설정

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		ShooterGamePlayTags::Shared_Event_Shoot,
		EventData
	);
}

void UShooterEnemyCombatComponent::TriggerGameplayEvent(
	const FGameplayTag EventTag,
	const FGameplayEventData& EventData
)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		EventTag,
		EventData
	);
}
