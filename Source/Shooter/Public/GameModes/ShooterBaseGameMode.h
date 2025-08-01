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

	UFUNCTION(BlueprintCallable)
	void OnPlayerDied();

	void OnAllEnemiesDefeated();

protected:

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

		UFUNCTION(BlueprintCallable)
	void StartWave();

	void EndGame(bool bIsWin);

private:

	UShooterGameInstance* GameInstance;
	FTimerHandle StartTime;
};
