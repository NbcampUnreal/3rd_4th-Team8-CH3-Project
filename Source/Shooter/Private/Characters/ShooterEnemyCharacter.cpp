#include "Characters/ShooterEnemyCharacter.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "DataAssets/StartUpDatas/DataAsset_StartUpDataBase.h"
#include "AIController.h"

AShooterEnemyCharacter::AShooterEnemyCharacter()
{
	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	CurWalkSpeed = 300.0f;
	Movement->MaxWalkSpeed = CurWalkSpeed;
	Movement->RotationRate = FRotator(0.0f, 100.0f, 0.0f);
	Movement->AirControl = 0.2f;
}

void AShooterEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(AIControllerClass, TEXT("AIControllerClass is null!"));
	
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
