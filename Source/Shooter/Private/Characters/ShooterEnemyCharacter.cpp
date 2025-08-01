#include "Characters/ShooterEnemyCharacter.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "DataAssets/StartUpDatas/DataAsset_StartUpDataBase.h"
#include "AIController.h"

AShooterEnemyCharacter::AShooterEnemyCharacter()
{
	
	ensureMsgf(AIControllerClass, TEXT("AIControllerClass is Null!"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AShooterEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ShooterAbilitySystemComponent)
	{
		ShooterAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			ShooterAttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &AShooterEnemyCharacter::OnHealthAttributeChanged);
	}

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(ShooterAbilitySystemComponent);
			UE_LOG(LogTemp, Warning, TEXT("AddStartUp Successed!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AddStartUp Failed!"));
	}

	if (ShooterAttributeSet)
	{
		float CurHealth = ShooterAttributeSet->GetCurrentHealth();
		float MaxHealth = ShooterAttributeSet->GetMaxHealth();
		UE_LOG(LogTemp, Warning, TEXT("CurHealth: %f / MaxHealth: %f"), CurHealth, MaxHealth);
	}
}

void AShooterEnemyCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}
