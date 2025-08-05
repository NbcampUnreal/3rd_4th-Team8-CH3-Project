// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Projectile/ShooterProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AShooterProjectileBase::AShooterProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	// 스피어컴포넌트 콜리전을 Projectile로 설정
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	// OnHit 함수 바인드
	CollisionComponent->OnComponentHit.AddDynamic(this, &AShooterProjectileBase::OnHit);
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(15.0f);

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMeshComponent->SetupAttachment(CollisionComponent);

	// 발사체 이동관련 컴포넌트
	// 1, 2: 생성 후. RootComponent(CollisionComponent)에 부착
	// 3: 발사체의 초기 속도
	// 4 : 발사체의 최대 속도(초기 속도와 같아 빨리지진 않음)
	// 5 : 이동 방향에 따라 회전할 것인지 설정.true면 이동방향으로 메쉬가 회전함
	// 6 : 발사체가 바닥에 닿은후 튕겨져 나올 것인지 여부.true면 팅김
	// 7 : 튕김 정도. 0.0f이면 튕기지 않고 현재는 조금씩 튕기는 정도가 줄어들음.
	// 8 : 발사체가 중력에 영향을 받을 것인지에 대한 정도.현재는 영향 X

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	CascadeEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("CascadeEffect"));
	CascadeEffectComponent->SetupAttachment(RootComponent);
}

void AShooterProjectileBase::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AShooterProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	OnProjectileHit.Broadcast(Hit);
}
