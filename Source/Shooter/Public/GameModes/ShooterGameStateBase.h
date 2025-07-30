#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ShooterGameStateBase.generated.h"

UCLASS()
class SHOOTER_API AShooterGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AShooterGameStateBase();

	UPROPERTY(BlueprintReadOnly)
	int32 AliveEnemyCount;

	UPROPERTY(BlueprintReadOnly)
	int32 TotalEnemy;

	void SetAliveEnemyCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	void OnEnemyDied();

};
