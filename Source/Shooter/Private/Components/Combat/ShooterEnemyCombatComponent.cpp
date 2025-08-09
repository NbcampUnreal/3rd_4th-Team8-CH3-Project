// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/ShooterEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ShooterGamePlayTag.h"
#include "Characters/ShooterEnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "Shooter/ShooterDebugHelper.h"

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
	//
	// UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
	// 	GetOwningPawn(),
	// 	ShooterGamePlayTags::Shared_Event_Shoot,
	// 	EventData
	// );

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		ShooterGamePlayTags::Shared_Event_MeleeHit,
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

void UShooterEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	const AShooterEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AShooterEnemyCharacter>();
	check(OwningEnemyCharacter);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();

	const ECollisionEnabled::Type CollisionQuery = bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;
	switch (ToggleDamageType)
	{
	case EToggleDamageType::EED_LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(CollisionQuery);
		break;

	case EToggleDamageType::EED_RightHand:
		RightHandCollisionBox->SetCollisionEnabled(CollisionQuery);
		break;

	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
