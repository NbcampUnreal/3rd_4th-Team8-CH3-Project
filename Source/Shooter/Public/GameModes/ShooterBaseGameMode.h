#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterBaseGameMode.generated.h"

class UShooterGameInstance;
class ATeleportPortal;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPortalSpawned, ATeleportPortal*, TeleportPortal);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveStarted, int32, WaveNumber);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveEnded, int32, WaveNumber);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, bClear);

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

	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FOnGameOver OnGameOver;

protected:

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

	void EndGame(bool bIsWin);

	UFUNCTION(BlueprintCallable)
	void RetryGame();

	UFUNCTION(BlueprintCallable)
	void ResetGame();

	UFUNCTION()
	void AfterDelay();

	UPROPERTY(EditDefaultsOnly, Category = "Portal")
	TSubclassOf<ATeleportPortal> PortalClass;

	//포탈 생성 기본 위치
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	FVector DefaultPortalLocation;

	//캐릭터와 포탈 생성 위치의 거리 차이 기준(해당 수치 만큼 떨어져 있어야함)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	float PortalRange;

	//PortalRange만큼 떨어지지 않았다면 포탈 생성 위치 변경(생성될 포탈과 플레이어 캐릭터의 위치 차이 + ChangeLocation만큼 떨어져서 생성)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	float ChangeLocation;

private:

	FVector CalculationPortalLocation();

	UShooterGameInstance* GameInstance;

	FTimerHandle StartTime;
};
