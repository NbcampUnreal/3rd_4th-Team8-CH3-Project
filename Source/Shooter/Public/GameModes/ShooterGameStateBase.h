#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ShooterGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyCountChanged, int32, AliveCount, int32, TotalCount);

UCLASS()
class SHOOTER_API AShooterGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:

	AShooterGameStateBase();

	void SetAliveEnemyCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	void OnEnemyDied();

	int32 GetTotalEnemy() {return TotalEnemy;}
	int32 GetAliveEnemyCount() {return AliveEnemyCount;}

	UPROPERTY(BlueprintAssignable)
	FOnEnemyCountChanged OnEnemyCountChanged;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 AliveEnemyCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalEnemy;

};
