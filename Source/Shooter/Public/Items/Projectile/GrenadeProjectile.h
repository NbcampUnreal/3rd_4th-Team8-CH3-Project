// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Projectile/ShooterProjectileBase.h"
#include "GrenadeProjectile.generated.h"

class AShooterBaseCharacter;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class SHOOTER_API AGrenadeProjectile : public AShooterProjectileBase
{
	GENERATED_BODY()

public:
	AGrenadeProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
	AShooterBaseCharacter* InstigatorCharacter;
protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* ExplosionCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grenade")
	TArray<AShooterBaseCharacter*> OverlappingCharacters;

	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FTimerHandle ExplosionTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Grenade|Damage")
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

	void OnExplosion();
};

