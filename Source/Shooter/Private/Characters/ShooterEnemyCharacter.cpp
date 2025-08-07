#include "Characters/ShooterEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "DataAssets/StartUpDatas/DataAsset_StartUpDataBase.h"
#include "AIController.h"
#include "Components/Combat/ShooterEnemyCombatComponent.h"
#include "Controllers/ShooterAIController.h"

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

UPawnCombatComponent* AShooterEnemyCharacter::GetPawnCombatComponent() const
{
	return ShooterEnemyCombatComponent;
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

		// StartupEffect가 적용된 이후 RunBehaviorTree를 호출하여 BTService에서 초기화된 속성을 사용할 수 있게함
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController && BehaviorTreeAsset)
		{
			AIController->RunBehaviorTree(BehaviorTreeAsset);
			Cast<AShooterAIController>(AIController)->InitBlackboardValues();
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

		float CurAttackRange = ShooterAttributeSet->GetAttackRange();
		UE_LOG(LogTemp, Warning, TEXT("AttckRange: %f"), CurAttackRange);
	}
}

void AShooterEnemyCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}
