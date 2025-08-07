#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class UBoxComponent;
class ACharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSpawnFinished, int32);

UCLASS()
class SHOOTER_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawner();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemies(const TArray<TSubclassOf<ACharacter>>& EnemyTypes, int32 TotalCount);

	FOnSpawnFinished& GetOnSpawnFinished() { return OnSpawnFinished; }

protected:

	FVector GetRandomPointInVolume(TSubclassOf<ACharacter>) const;
	
	void MultiSpawnEnemy();

	FOnSpawnFinished OnSpawnFinished;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MultipleSpawn")
	int32 MultipleSpawn = 3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MultipleSpawn")
	int32 SpawnInterval = 3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MultipleSpawn")
	int32 RetrySpawn = 3;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawningBox;

	int32 MaxSpawnCount;
	int32 SpawnedCount;
	int32 SpawnRty = 0;
	TArray<TSubclassOf<ACharacter>> CacheEnemyType;
	FTimerHandle SpawnTimerHandle;

};
