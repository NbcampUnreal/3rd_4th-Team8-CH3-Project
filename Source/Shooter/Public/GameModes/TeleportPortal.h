#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportPortal.generated.h"

class USphereComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountDown, int32, CountDownTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerInPortal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerOutPortal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyPortal);

UCLASS()
class SHOOTER_API ATeleportPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleportPortal();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnCountDown OnCountDown;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerInPortal OnPlayerInPortal;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerOutPortal OnPlayerOutPortal;

	FOnDestroyPortal OnDestroyPortal;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timer")
	int32 CountDownTimer;

private:

	UPROPERTY(VisibleAnywhere, Category="Component")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere,Category="Component")
	USphereComponent* TrigerZone;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* PortalMesh;

	FTimerHandle PortalTimerHandle;
	AActor* OverlapActor;
	int32 CountTime;

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

	UFUNCTION()
	void ResetPortalState();
};
