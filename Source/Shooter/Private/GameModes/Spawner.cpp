#include "GameModes/Spawner.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
}


int32 ASpawner::SpawnEnemies(const TArray<TSubclassOf<ACharacter>>& EnemyTypes, int32 TotalCount)
{

	int32 SpawnedCount = 0;
	
	if (EnemyTypes.Num() == 0 || TotalCount <= 0)
	{
		return SpawnedCount;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return SpawnedCount;
	}

	for (int32 i = 0; i < TotalCount; ++i)
	{
		int32 Index = FMath::RandRange(0, EnemyTypes.Num() - 1);
		TSubclassOf<ACharacter> EnemyClass = EnemyTypes[Index];
		if (!EnemyClass) continue;

		FVector SpawnLocation = GetRandomPointInVolume(EnemyClass);
		
		//스폰 충돌 시 위치를 조절하여 스폰하도록 설정
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ACharacter* SpawnedEnemy = World->SpawnActor<ACharacter>(
			EnemyClass,
			SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams

		);

		if (SpawnedEnemy)
		{
			SpawnedCount++;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Random spawned %d enemies from %d types"), SpawnedCount, EnemyTypes.Num());

	return SpawnedCount;
}

FVector ASpawner::GetRandomPointInVolume(TSubclassOf<ACharacter> EnemyClass) const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	FVector Start = BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		BoxExtent.Z
	);

	FVector End = Start - FVector(0, 0, BoxExtent.Z * 3.0f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// 지면과 충돌 여부 확인
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		//정상적으로 라인트레이스 인식해서 spawn되는지 확인
		//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.0f, 0, 2.0f);
		//DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 12.0f, FColor::Red, false, 5.0f);

		// 캡슐 크기 기본값 설정
		float HalfHeight = 88.f;
		if(EnemyClass)
		{
			ACharacter* CharObj = EnemyClass->GetDefaultObject<ACharacter>();
			if (CharObj && CharObj->GetCapsuleComponent())
			{
				HalfHeight = CharObj->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			}
		}
		return Hit.ImpactPoint + FVector(0, 0, HalfHeight);
	}

	// 실패 시 그냥 원래 위치 반환
	return Start;
}
