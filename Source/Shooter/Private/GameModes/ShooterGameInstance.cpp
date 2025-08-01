#include "GameModes/ShooterGameInstance.h"
#include "Kismet/GameplayStatics.h"

UShooterGameInstance::UShooterGameInstance()
{
	MaxWave = 0;
	CurrentWave = 0;
}

void UShooterGameInstance::Init()
{
	Super::Init();

	if (LevelDataTable)
	{
		TArray<FWaveConfig*> Rows;
		LevelDataTable->GetAllRows<FWaveConfig>(TEXT("LevelDataTable"), Rows);

		for (const FWaveConfig* Row : Rows)
		{
			if (Row)
			{
				WaveConfigs.Add(*Row);
			}
		}
		MaxWave = WaveConfigs.Num();

		//데이터테이블 정상적으로 가져왔는지 확인
		for (int i = 0; i < WaveConfigs.Num(); i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("FWaveConfig : %d,   WaveLevel : %s"), i, *WaveConfigs[i].LevelName.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelDataTable is not assigned!"));
	}

}


void UShooterGameInstance::NextWaveLevel()
{
	if (WaveConfigs.IsValidIndex(CurrentWave))
	{
		FName LevelToLoad = WaveConfigs[CurrentWave].LevelName;
		if (!GetWorld())
		{
			UE_LOG(LogTemp, Error, TEXT("GameInstance not found! (GameInstance : Line 50)"));
			return;
		}
		UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid wave index(-1): %d"), CurrentWave);
	}
}

