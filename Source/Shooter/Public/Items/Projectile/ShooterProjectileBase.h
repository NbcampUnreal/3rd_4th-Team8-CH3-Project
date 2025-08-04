// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTER_API AShooterProjectileBase : public AActor
{
	GENERATED_BODY()
public:
    // Sets default values for this actor's properties
    AShooterProjectileBase();

    //발사 방향으로의 발사체 속도를 초기화하는 함수입
    UFUNCTION(BlueprintCallable, Category = Projectile)
    void FireInDirection(const FVector& ShootDirection);

    // 발사체가 어딘가에 부딪힐 때 호출되는 함수.
    UFUNCTION(BlueprintCallable, Category = Projectile)
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileHit, const FHitResult&, HitResult);

    UPROPERTY(BlueprintAssignable, Category = Projectile)
    FOnProjectileHit OnProjectileHit;

protected:
    //콜리전 컴포넌트
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    USphereComponent* CollisionComponent;

    // 발사체 이동 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = Movement)
    UProjectileMovementComponent* ProjectileMovementComponent;

    // 발사체 메시
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    UStaticMeshComponent* ProjectileMeshComponent;
};

