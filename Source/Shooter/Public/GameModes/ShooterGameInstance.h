#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

class ACharacter;

USTRUCT(BlueprintType)
struct FWaveConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ACharacter>> EnemyClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalEnemyCount;
};

UCLASS()
class SHOOTER_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UShooterGameInstance();
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void NextWaveLevel();

	int32 GetCurrentWave() const { return CurrentWave; }
	
	void SetCurrentWave(int32 SetWave) { CurrentWave = SetWave;}
	
	int32 GetMaxWave() const { return MaxWave; }
	
	const TArray<FWaveConfig>& GetWaveConfigs() const { return WaveConfigs; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	UDataTable* LevelDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxWave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FWaveConfig> WaveConfigs;

};
