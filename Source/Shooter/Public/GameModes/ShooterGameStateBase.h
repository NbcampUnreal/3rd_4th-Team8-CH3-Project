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

	void SetAliveEnemyCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	void OnEnemyDied();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 AliveEnemyCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalEnemy;

};
