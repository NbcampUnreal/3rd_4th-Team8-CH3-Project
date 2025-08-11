#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterBaseGameMode.generated.h"

class UShooterGameInstance;
class ATeleportPortal;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPortalSpawned, ATeleportPortal*, TeleportPortal);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveStarted, int32, WaveNumber);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveEnded, int32, WaveNumber);

UCLASS()
class SHOOTER_API AShooterBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AShooterBaseGameMode();

	UFUNCTION(BlueprintCallable)
	void OnPlayerDied();

	void OnAllEnemiesDefeated();

	UFUNCTION(BlueprintCallable)
	void StartWave();

	UPROPERTY(BlueprintAssignable)
	FPortalSpawned PortalSpawned;

	UPROPERTY(BlueprintAssignable, Category = "Wave")
	FOnWaveStarted OnWaveStarted;

	UPROPERTY(BlueprintAssignable, Category = "Wave")
	FOnWaveEnded OnWaveEnded;

protected:

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

	void EndGame(bool bIsWin);

	UPROPERTY(EditDefaultsOnly, Category = "Portal")
	TSubclassOf<ATeleportPortal> PortalClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	FVector PortalLocation;

private:

	UShooterGameInstance* GameInstance;

	FTimerHandle StartTime;
};
