// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShooterBaseCharacter.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/ShooterAttributeSet.h"

AShooterBaseCharacter::AShooterBaseCharacter()
{
	// PrimaryActorTick.bCanEverTick = false;
	// PrimaryActorTick.bStartWithTickEnabled = false; ALS 플러그인에서 관리

	ShooterAbilitySystemComponent = CreateDefaultSubobject<UShooterAbilitySystemComponent>(
		TEXT("ShooterAbilitySystemComponent"));

	ShooterAttributeSet = CreateDefaultSubobject<UShooterAttributeSet>(TEXT("ShooterAttributeSet"));

	GetMesh()->bReceivesDecals = true;
}

UAbilitySystemComponent* AShooterBaseCharacter::GetAbilitySystemComponent() const
{
	return GetShooterAbilitySystemComponent();
}

UPawnCombatComponent* AShooterBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AShooterBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void AShooterBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (ShooterAbilitySystemComponent)
	{
		// 액터정보를 설정하는 부분
		ShooterAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("start up 데이터를 character에 할당하는 것을 잊었습니다 %s!"), *GetName());
	}
}
