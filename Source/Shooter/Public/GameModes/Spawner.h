#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class UBoxComponent;
class ACharacter;

UCLASS()
class SHOOTER_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawner();

	UFUNCTION(BlueprintCallable)
	int32 SpawnEnemies(const TArray<TSubclassOf<ACharacter>>& EnemyTypes, int32 TotalCount);

protected:

	FVector GetRandomPointInVolume(TSubclassOf<ACharacter>) const;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawningBox;
};
