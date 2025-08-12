#include "GameModes/ShooterBaseGameMode.h"
#include "GameModes/ShooterGameStateBase.h"
#include "GameModes/Spawner.h"
#include "GameModes/ShooterGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/ShooterController.h"
#include "Characters/ShooterCharacter.h"
#include "GameModes/TeleportPortal.h"
#include "GameFramework/Character.h"

AShooterBaseGameMode::AShooterBaseGameMode()
{
	DefaultPawnClass = AShooterCharacter::StaticClass();
	PlayerControllerClass = AShooterController::StaticClass();
	GameStateClass = AShooterGameStateBase::StaticClass();

	DefaultPortalLocation = FVector(0.0f, 0.0f, 150.0f);
	PortalRange = 250.0f;
	ChangeLocation = 400.0f;
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
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameMode : Line 50)"));
		return;
	}

	GameInstance->LoadWaveLevel();
	
}

void AShooterBaseGameMode::StartWave()
{
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameMode : Line 62)"));
		return;
	}

	AShooterGameStateBase* GS = GetGameState<AShooterGameStateBase>();
	if (!GS)
	{
		UE_LOG(LogTemp, Error, TEXT("GetGameState not found! (GameMode : Line 72)"));
		return;
	}

	//실제 웨이브 수와 구조체의 배열의 수는 -1 차이남 ex) wave1 = 구조체[0]
	int32 CurrentWave = GameInstance->GetCurrentWave();
	GameInstance->SetCurrentWave(CurrentWave + 1);
	
	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start"), CurrentWave + 1);
	
	if (!GameInstance->GetWaveConfigs().IsValidIndex(CurrentWave)) return;

	const FWaveConfig& WaveData = GameInstance->GetWaveConfigs()[CurrentWave];
	const TArray<TSubclassOf<ACharacter>>& EnemyTypes = WaveData.EnemyClasses;
	const int32 SpawnCount = WaveData.TotalEnemyCount;

	TArray<AActor*> SpawnerActors;
	UGameplayStatics::GetAllActorsOfClass(this, ASpawner::StaticClass(), SpawnerActors);

	for (AActor* Actor : SpawnerActors)
	{
		if (ASpawner* Spawner = Cast<ASpawner>(Actor))
		{
			Spawner->GetOnSpawnFinished().AddLambda([SpawnCount, GS](int32 FinishedSpawnCount)
			{
				if (SpawnCount == FinishedSpawnCount)
				{
					UE_LOG(LogTemp, Warning, TEXT("All spawns completed"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Some spawns failed (%d / %d)"), FinishedSpawnCount, SpawnCount);
					GS->SetAliveEnemyCount(FinishedSpawnCount);
				}
				
			});

			Spawner->SpawnEnemies(EnemyTypes, SpawnCount);

		}
	}

	GS->SetAliveEnemyCount(SpawnCount);
	OnWaveStarted.Broadcast(GameInstance->GetCurrentWave());
	
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
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameMode : Line 112)"));
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
		OnWaveEnded.Broadcast(GameInstance->GetCurrentWave());
		//여기서 포탈 생성해줌
		if (PortalClass)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				ATeleportPortal* Portal = World->SpawnActor<ATeleportPortal>(
					PortalClass,
					CalculationPortalLocation(),
					FRotator::ZeroRotator,
					SpawnParams
				);

				PortalSpawned.Broadcast(Portal);
			}
		}
	}
}

FVector AShooterBaseGameMode::CalculationPortalLocation()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return DefaultPortalLocation;
	}

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(World ,0);
	if (!PlayerCharacter)
	{
		return DefaultPortalLocation;
	}
	FVector PlayerLoc = PlayerCharacter->GetActorLocation();

	FVector Diff = DefaultPortalLocation - PlayerLoc; //생성될 포탈과 플레이어 캐릭터의 위치 차이 계산
	float Dist = Diff.Size2D();

	FVector PortalLocation;

	if (Dist < PortalRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("The distance between the character and the portal is close."));

		FVector Dir = Diff.GetSafeNormal2D();

		PortalLocation = PlayerLoc + Dir * ChangeLocation;
	}
	else
	{
		PortalLocation = DefaultPortalLocation;
	}

	return PortalLocation;
}

void AShooterBaseGameMode::EndGame(bool bIsWin)
{
	UE_LOG(LogTemp, Warning, TEXT("End Game!!!"));
	
	if (!GameInstance)
	{
		return;
	}
	GameInstance->SetCurrentWave(0);
	//게임 종료 시 이겼나 졌나로 분기처리하여 플레이어에게 보여줄 화면?
}