#include "GameModes/ShooterGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/ShooterBaseGameMode.h"

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

void UShooterGameInstance::LoadWaveLevel()
{
	//이전 레벨 언로드
	UnloadStreamLevel();
	
	//다음레벨 로드
	FName LevelToLoad = WaveConfigs[CurrentWave].LevelName;

	FLatentActionInfo LatentInfo;									//콜백 함수 정보
	LatentInfo.CallbackTarget = this;								//콜백 타겟
	LatentInfo.ExecutionFunction = FName("LoadLevelComplete");		//실제로 호출할 함수명
	LatentInfo.UUID = 1;											//고유 식별 번호
	LatentInfo.Linkage = 0;											//특수한 흐름 제어가 필요한 경우만 수정 일반적으로 0 고정

	UGameplayStatics::LoadStreamLevel(
		this,														//함수에 호출될 월드 this나 GetWolrd
		LevelToLoad,												//로드할 레벨 이름
		true,														//로딩 완료 후 자동으로 화면에 보이게 할지 여부
		true,														//레벨로딩을 동기화 할지 여부 (true : 로딩 완료될 때까지 다른작업 차단)
		LatentInfo													//로딩이 완료된 후 실행할 콜백 함수 정보
	);

	UE_LOG(LogTemp, Warning, TEXT("Started loading level: %s"), *LevelToLoad.ToString());
}

void UShooterGameInstance::UnloadStreamLevel()
{

	for (int32 WaveNum = 0; WaveNum < GetWaveConfigs().Num(); WaveNum++)
	{
		FName LevelName = GetWaveConfigs()[WaveNum].LevelName;
		ULevelStreaming* StreamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelName);
		if (!StreamingLevel)
		{
			UE_LOG(LogTemp, Warning, TEXT("StreamingLevel not found!"));
			continue;
		}

		bool bLoaded = StreamingLevel->IsLevelLoaded();    // 메모리에 로드되었는지
		bool bVisible = StreamingLevel->IsLevelVisible();   // 화면에 보이는 상태인지
		UE_LOG(LogTemp, Log, TEXT("Level%d  Loaded: %d, Visible: %d"), WaveNum, bLoaded, bVisible);

		if (bLoaded && bVisible)
		{
			FLatentActionInfo Latent;
			Latent.CallbackTarget = this;
			Latent.ExecutionFunction = NAME_None;
			Latent.Linkage = 0;
			Latent.UUID = FMath::Rand(); // 각 호출마다 다른 UUID

			UGameplayStatics::UnloadStreamLevel(
				this,
				LevelName,
				Latent,
				true
			);
			
			UE_LOG(LogTemp, Warning, TEXT("Unload PrevLevel: %s"), *LevelName.ToString());
		}

	}
}

void UShooterGameInstance::LoadLevelComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("Wave level streamed in successfully"));

	UWorld* World = GetWorld();
	if (!World) return;

	AShooterBaseGameMode* GM = World->GetAuthGameMode<AShooterBaseGameMode>();
	if (GM)
	{
		GM->StartWave();
	}
}

