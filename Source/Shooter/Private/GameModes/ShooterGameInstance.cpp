#include "GameModes/ShooterGameInstance.h"
#include "Kismet/GameplayStatics.h"

UShooterGameInstance::UShooterGameInstance()
{
	MaxWave = 4;
	CurrentWave = 0;
}

void UShooterGameInstance::Init()
{
	Super::Init();

	if (WaveLevelNames.IsEmpty())
	{
		for (int32 i = 1; i <= MaxWave; ++i)
		{
			FString LevelName = FString::Printf(TEXT("Level%d"), i);
			WaveLevelNames.Add(FName(*LevelName));
		}
	}
}


void UShooterGameInstance::NextWaveLevel()
{
	if (WaveLevelNames.IsValidIndex(CurrentWave))
	{
		UGameplayStatics::OpenLevel(GetWorld(), WaveLevelNames[CurrentWave]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid wave index(-1): %d"), CurrentWave);
	}
}

