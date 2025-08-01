// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/ShooterEnemyCharacter.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "DataAssets/StartUpDatas/DataAsset_StartUpDataBase.h"
#include "AIController.h"

AShooterEnemyCharacter::AShooterEnemyCharacter()
{
	if (!AIControllerClass)
	{
		ensureMsgf(AIControllerClass, TEXT("AIControllerClass is Null!"));
	}
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AShooterEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ShooterAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ShooterAttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &AShooterEnemyCharacter::OnHealthAttributeChanged);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(ShooterAbilitySystemComponent);
			UE_LOG(LogTemp, Warning, TEXT("AddStartUp Successed!"));
		}
	}

	float CurHealth = ShooterAttributeSet->GetCurrentHealth();
	float MaxHealth = ShooterAttributeSet->GetMaxHealth();
	UE_LOG(LogTemp, Warning, TEXT("CurHealth: %f / MaxHealth: %f"), CurHealth, MaxHealth);

}

void AShooterEnemyCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}
