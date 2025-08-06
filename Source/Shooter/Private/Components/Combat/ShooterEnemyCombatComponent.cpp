// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/ShooterEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

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
