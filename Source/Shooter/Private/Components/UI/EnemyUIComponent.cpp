// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/EnemyUIComponent.h"
#include "Characters/ShooterEnemyCharacter.h"

void UEnemyUIComponent::BroadcastEnemyUIDead(AShooterEnemyCharacter* EnemyActor)
{
	OnEnemyUIDead.Broadcast(EnemyActor);
}
