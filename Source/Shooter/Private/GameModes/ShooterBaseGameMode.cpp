#include "GameModes/ShooterBaseGameMode.h"
#include "GameModes/ShooterGameStateBase.h"
#include "GameModes/Spawner.h"
#include "GameModes/ShooterGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/ShooterController.h"
#include "Characters/ShooterCharacter.h"

AShooterBaseGameMode::AShooterBaseGameMode()
{
	DefaultPawnClass = AShooterCharacter::StaticClass();
	PlayerControllerClass = AShooterController::StaticClass();
	GameStateClass = AShooterGameStateBase::StaticClass();
}

void AShooterBaseGameMode::StartPlay()
{
	Super::StartPlay();

	GameInstance = Cast<UShooterGameInstance>(GetGameInstance());
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found!"));
		return;
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		GetWorldTimerManager().SetTimer(
			StartTime,
			this,
			&AShooterBaseGameMode::StartGame,
			3.0f,
			false
		);
	}
	else
	{
		StartWave();
	}
}

void AShooterBaseGameMode::StartGame()
{
	GetWorldTimerManager().ClearTimer(StartTime);
	GameInstance->NextWaveLevel();
}

void AShooterBaseGameMode::StartWave()
{
	GameInstance->CurrentWave++;
	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start"), GameInstance->CurrentWave);

	TArray<AActor*> SpawnerActors;
	UGameplayStatics::GetAllActorsOfClass(this, ASpawner::StaticClass(), SpawnerActors);

	int32 TotalSpawnedEnemies = GameInstance->CurrentWave;

	for (AActor* Actor : SpawnerActors)
	{
		if (ASpawner* Spawner = Cast<ASpawner>(Actor))
		{
			Spawner->SpawnEnemies(TotalSpawnedEnemies);
		}
	}

	AShooterGameStateBase* GS = GetGameState<AShooterGameStateBase>();
	if (GS)
	{
		GS->SetAliveEnemyCount(GameInstance->CurrentWave);
	}
}

void AShooterBaseGameMode::OnAllEnemiesDefeated()
{
	if (GameInstance->CurrentWave >= GameInstance->MaxWave)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clear all waves"));
		EndGame(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Clear wave %d"), GameInstance->CurrentWave);
		GameInstance->NextWaveLevel();
	}
}

void AShooterBaseGameMode::EndGame(bool bIsWin)
{
	UE_LOG(LogTemp, Warning, TEXT("End Game!!!"));
	GameInstance->CurrentWave = 0;
	//게임 종료 시 이겼나 졌나로 분기처리하여 플레이어에게 보여줄 화면?
}
