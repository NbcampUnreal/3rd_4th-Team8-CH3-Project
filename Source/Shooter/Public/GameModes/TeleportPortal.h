#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportPortal.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class SHOOTER_API ATeleportPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleportPortal();

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timer")
	int32 CountTime;

private:

	UPROPERTY(VisibleAnywhere, Category="Component")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere,Category="Component")
	USphereComponent* TrigerZone;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* PortalMesh;

	FTimerHandle PortalTimerHandle;
	AActor* OverlapActor;

	UFUNCTION()
	void TeleportHandle();

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
