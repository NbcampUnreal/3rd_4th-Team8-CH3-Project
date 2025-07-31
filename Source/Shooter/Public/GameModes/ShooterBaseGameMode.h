#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterBaseGameMode.generated.h"

class UShooterGameInstance;

UCLASS()
class SHOOTER_API AShooterBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterBaseGameMode();
	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void StartWave();

	void OnAllEnemiesDefeated();
	void EndGame(bool bIsWin);

private:
	UShooterGameInstance* GameInstance;

	FTimerHandle StartTime;
};
