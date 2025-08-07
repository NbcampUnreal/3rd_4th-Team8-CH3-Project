#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterBaseGameMode.generated.h"

class UShooterGameInstance;
class ATeleportPortal;

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
