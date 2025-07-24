// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShooterBaseCharacter.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"

AShooterBaseCharacter::AShooterBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ShooterAbilitySystemComponent = CreateDefaultSubobject<UShooterAbilitySystemComponent>(
		TEXT("ShooterAbilitySystemComponent"));

	GetMesh()->bReceivesDecals = true;
}

UAbilitySystemComponent* AShooterBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AShooterBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
