#include "Characters/ShooterEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/ShooterAttributeSet.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "DataAssets/StartUpDatas/DataAsset_StartUpDataBase.h"
#include "AIController.h"
#include "ShooterFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/ShooterEnemyCombatComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Engine/AssetManager.h"

AShooterEnemyCharacter::AShooterEnemyCharacter()
{
	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	CurWalkSpeed = 300.0f;
	Movement->MaxWalkSpeed = CurWalkSpeed;
	Movement->RotationRate = FRotator(0.0f, 100.0f, 0.0f);
	Movement->AirControl = 0.2f;

	ShooterEnemyCombatComponent = CreateDefaultSubobject<UShooterEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
}

UPawnCombatComponent* AShooterEnemyCharacter::GetPawnCombatComponent() const
{
	return ShooterEnemyCombatComponent;
}

UPawnUIComponent* AShooterEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AShooterEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AShooterEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(AIControllerClass, TEXT("AIControllerClass is null!"));

	if (ShooterAbilitySystemComponent)
	{
		ShooterAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			ShooterAttributeSet->GetCurrentHealthAttribute()).AddUObject(
			this, &AShooterEnemyCharacter::OnHealthAttributeChanged);
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

		float CurAttackRange = ShooterAttributeSet->GetAttackRange();
		UE_LOG(LogTemp, Warning, TEXT("AttckRange: %f"), CurAttackRange);
	}
}

void AShooterEnemyCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}

void AShooterEnemyCharacter::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}

void AShooterEnemyCharacter::OnBodyCollisionBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UShooterFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			ShooterEnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void AShooterEnemyCharacter::InitEnemyStartUpData()
{
	// 만약 CharacterStartUpData가 null이라면 (즉, 설정된 에셋이 없다면), 함수 종료
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	// 에셋 매니저를 통해 소프트 오브젝트 경로를 비동기로 로드
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(), // 로드할 에셋의 경로 지정
		FStreamableDelegate::CreateLambda( // 로드 완료 시 호출할 콜백 람다 함수 정의
			[this]() // 현재 객체(this)를 캡처하여 멤버에 접근할 수 있도록 설정
			{
				// 로드가 완료되었으므로 실제 데이터 에셋 객체 포인터를 가져옴
				if (UDataAsset_StartUpDataBase* LoadData = CharacterStartUpData.Get())
				{
					// 로드된 스타트업 데이터를 사용해 AbilitySystemComponent에 능력 부여
					LoadData->GiveToAbilitySystemComponent(ShooterAbilitySystemComponent);
				}
			}
		)
	);
}
