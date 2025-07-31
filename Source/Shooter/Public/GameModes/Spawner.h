#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class UBoxComponent;

UCLASS()
class SHOOTER_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnEnemy")
	TSubclassOf<class ACharacter> EnemyClass;

	void SpawnEnemies(int32 NumEnemies);

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawningBox;

	FVector GetRandomPointInVolume() const;
};
