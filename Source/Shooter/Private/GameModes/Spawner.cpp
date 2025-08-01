#include "GameModes/Spawner.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
}


int32 ASpawner::SpawnEnemies(const TArray<TSubclassOf<class ACharacter>>& EnemyTypes, int32 TotalCount)
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

		FVector SpawnLocation = GetRandomPointInVolume();
		
		ACharacter* SpawnedEnemy = World->SpawnActor<ACharacter>(
			EnemyClass,
			SpawnLocation,
			FRotator::ZeroRotator
		);

		if (SpawnedEnemy)
		{
			SpawnedCount++;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Random spawned %d enemies from %d types"), SpawnedCount, EnemyTypes.Num());

	return SpawnedCount;
}

FVector ASpawner::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}
