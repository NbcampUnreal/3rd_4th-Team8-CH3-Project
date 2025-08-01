#include "GameModes/ShooterBaseGameMode.h"
#include "GameModes/ShooterGameStateBase.h"
#include "GameModes/Spawner.h"
#include "GameModes/ShooterGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/ShooterController.h"
#include "Characters/ShooterCharacter.h"
#include "GameFramework/Character.h"

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
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameMode : Line 24)"));
		return;
	}

	FString CleanMapName = UGameplayStatics::GetCurrentLevelName(this, true);
	if (CleanMapName.Equals("MenuLevel"))
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
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameMode : Line 51)"));
		return;
	}
	GameInstance->NextWaveLevel();
	

}

void AShooterBaseGameMode::StartWave()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameMode : Line 63)"));
		return;
	}

	//실제 웨이브 수와 구조체의 배열의 수는 -1 차이남 ex) wave1 = 구조체[0]
	int CurrentWave = GameInstance->GetCurrentWave();
	GameInstance->SetCurrentWave(CurrentWave + 1);
	
	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start"), CurrentWave + 1);
	

	if (!GameInstance->GetWaveConfigs().IsValidIndex(CurrentWave)) return;

	const FWaveConfig& WaveData = GameInstance->GetWaveConfigs()[CurrentWave];
	const TArray<TSubclassOf<ACharacter>>& EnemyTypes = WaveData.EnemyClasses;
	int32 SpawnedCount = 0;

	TArray<AActor*> SpawnerActors;
	UGameplayStatics::GetAllActorsOfClass(this, ASpawner::StaticClass(), SpawnerActors);

	for (AActor* Actor : SpawnerActors)
	{
		if (ASpawner* Spawner = Cast<ASpawner>(Actor))
		{
			SpawnedCount = Spawner->SpawnEnemies(EnemyTypes, WaveData.TotalEnemyCount);
			if (SpawnedCount != WaveData.TotalEnemyCount)
			{
				UE_LOG(LogTemp, Warning, TEXT("The number requested and the number spawned are different : requst %d  /  respone %d"), WaveData.TotalEnemyCount, SpawnedCount);
			}
		}
	}

	AShooterGameStateBase* GS = GetGameState<AShooterGameStateBase>();
	if (GS)
	{
		int32 index = CurrentWave;
		GS->SetAliveEnemyCount(SpawnedCount);
	}
}

void AShooterBaseGameMode::OnPlayerDied()
{
	UE_LOG(LogTemp, Warning, TEXT("The player died"));
	EndGame(false);
}

void AShooterBaseGameMode::OnAllEnemiesDefeated()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameMode : Line 109)"));
		return;
	}
	if (GameInstance->GetCurrentWave() >= GameInstance->GetMaxWave())
	{
		UE_LOG(LogTemp, Warning, TEXT("Clear all waves"));
		EndGame(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Clear wave %d"), GameInstance->GetCurrentWave());
		GameInstance->NextWaveLevel();
	}
}

void AShooterBaseGameMode::EndGame(bool bIsWin)
{
	UE_LOG(LogTemp, Warning, TEXT("End Game!!!"));
	
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameMode : Line 130)"));
		return;
	}
	GameInstance->SetCurrentWave(0);
	//게임 종료 시 이겼나 졌나로 분기처리하여 플레이어에게 보여줄 화면?
}
