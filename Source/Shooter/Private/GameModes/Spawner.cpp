#include "GameModes/Spawner.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
// #include "tmp/TempC.h"


ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
}

void ASpawner::SpawnEnemies(int32 NumEnemies)
{
	if (!EnemyClass)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (int32 i = 0; i < NumEnemies; ++i)
	{
		FVector SpawnLocation = GetRandomPointInVolume();
		World->SpawnActor<ACharacter>(
			EnemyClass,
			SpawnLocation,
			FRotator::ZeroRotator
		);
	}

	UE_LOG(LogTemp, Warning, TEXT("Enemy spawned :%d"), NumEnemies);
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
