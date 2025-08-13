#include "GameModes/Spawner.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
}


void ASpawner::SpawnEnemies(const TArray<TSubclassOf<ACharacter>>& EnemyTypes, int32 TotalCount, FName LevelName)
{
	CacheEnemyType = EnemyTypes;
	MaxSpawnCount = TotalCount;
	SpawnedCount = 0;
	SubLevelName = LevelName;
	MultiSpawn = MultipleSpawn;
	
	if (CacheEnemyType.Num() == 0 || MaxSpawnCount <= 0)
	{
		return ;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	//즉시 1회 스폰
	MultiSpawnEnemy();

	//
	World->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASpawner::MultiSpawnEnemy,
		SpawnInterval,
		true
	);
}

void ASpawner::MultiSpawnEnemy()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	//n마리씩 스폰하고 남은 수만큼 MultipleSpawn 변경
	if ((MaxSpawnCount - SpawnedCount) < MultiSpawn)
	{
		MultiSpawn = (MaxSpawnCount - SpawnedCount) % MultiSpawn;
	}

	int32 RetryCount = 0;
	for (int32 Spawning = 0; Spawning < MultiSpawn; ++Spawning)
	{
		int32 Index = FMath::RandRange(0, CacheEnemyType.Num() - 1);
		TSubclassOf<ACharacter> EnemyClass = CacheEnemyType[Index];
		if (!EnemyClass) continue;

		FVector SpawnLocation = GetRandomPointInVolume(EnemyClass);

		ULevelStreaming* LS = UGameplayStatics::GetStreamingLevel(this, SubLevelName);
		if (!LS || !LS->IsLevelLoaded())
		{
			return;
		}

		//스폰 충돌 시 위치를 조절하여 스폰하도록 설정
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.OverrideLevel = LS->GetLoadedLevel();

		ACharacter* SpawnedEnemy = World->SpawnActor<ACharacter>(
			EnemyClass,
			SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams
		);

		if (SpawnedEnemy)
		{
			SpawnedCount++;
			SpawnTry++;
			RetryCount = 0;
		}
		else
		{
			RetryCount++;
			if (RetryCount > RetrySpawn)
			{
				SpawnTry++;
				RetryCount = 0;
			}
		}

		if (SpawnTry >= MaxSpawnCount)
		{
			UE_LOG(LogTemp, Warning, TEXT("Random spawned success %d enemies from %d types"), SpawnedCount, CacheEnemyType.Num());
			GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

			//마지막 스폰까지 완료했으면 델리게이트 호출 (BaseGameMode에서 받게끔)
			OnSpawnFinished.Broadcast(SpawnedCount);

			return;
		}
	}
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
