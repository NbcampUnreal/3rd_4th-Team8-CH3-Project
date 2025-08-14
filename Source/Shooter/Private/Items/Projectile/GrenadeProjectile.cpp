// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Projectile/GrenadeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/ShooterEnemyCharacter.h"
#include "Characters/ShooterCharacter.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/ShooterAttributeSet.h"

AGrenadeProjectile::AGrenadeProjectile()
{
	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(150.f);
	ExplosionCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ExplosionCollision->SetupAttachment(CollisionComponent);
	ExplosionCollision->OnComponentBeginOverlap.AddDynamic(this, &AGrenadeProjectile::OnOverlapBegin);
	ExplosionCollision->OnComponentEndOverlap.AddDynamic(this, &AGrenadeProjectile::OnOverlapEnd);

	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 2000.0f;
	ProjectileMovementComponent->Bounciness = 0.5f;
	ProjectileMovementComponent->ProjectileGravityScale = 1.5f;

}

void AGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();

	// 3초 뒤에 OnExplode 함수 실행
	GetWorldTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AGrenadeProjectile::OnExplosion,
		3.0f,
		false
	);

	if (AActor* InstigatorActor = GetInstigator())
	{
		// 캐릭터로 캐스트 시도
		if (AShooterCharacter* ShooterChar = Cast<AShooterCharacter>(InstigatorActor))
		{
			InstigatorCharacter = ShooterChar;
			UE_LOG(LogTemp, Log, TEXT("Instigator 캐릭터 할당 성공: %s"), *ShooterChar->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Instigator가 ShooterBaseCharacter가 아님"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Instigator가 없음"));
	}
}

void AGrenadeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		AShooterBaseCharacter* HitCharacter = Cast<AShooterBaseCharacter>(OtherActor);
		if (HitCharacter)
		{
			BP_OnSpawnProjectileHiFX(Hit.ImpactPoint);
			OnExplosion();
		}
	}
}

void AGrenadeProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AShooterEnemyCharacter* BaseChar = Cast<AShooterEnemyCharacter>(OtherActor))
	{
		if (!OverlappingCharacters.Contains(BaseChar))
		{
			OverlappingCharacters.Add(BaseChar);
		}
	}
}

void AGrenadeProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AShooterEnemyCharacter* BaseChar = Cast<AShooterEnemyCharacter>(OtherActor))
	{
		if (OverlappingCharacters.Contains(BaseChar))
		{
			OverlappingCharacters.Remove(BaseChar);
		}
	}
}

void AGrenadeProjectile::OnExplosion()
{
	// 타이머 정리
	GetWorldTimerManager().ClearTimer(ExplosionTimerHandle);

	UE_LOG(LogTemp, Warning, TEXT("[Grenade] OnExplosion called"));
	UE_LOG(LogTemp, Warning, TEXT("[Grenade] InstigatorCharacter: %s"),
		InstigatorCharacter ? *InstigatorCharacter->GetName() : TEXT("None"));


	

	for (int32 i = 0; i < OverlappingCharacters.Num(); i++)
	{
		AShooterEnemyCharacter* Character = OverlappingCharacters[i];

		if (!IsValid(Character))
		{
			continue;
		}

		UShooterAbilitySystemComponent* TargetASC = Character->GetShooterAbilitySystemComponent();
		if (!TargetASC)
		{
			continue;
		}

		if (!DamageGameplayEffect)
		{
			continue;
		}

		// EffectContext 생성
		FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();

		// 수류탄 자체를 Source로 등록
		EffectContext.AddSourceObject(this);

		// InstigatorCharacter 지정
		if (InstigatorCharacter)
		{
			EffectContext.AddInstigator(InstigatorCharacter, InstigatorCharacter);
		}

		// Spec 생성
		FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageGameplayEffect, 1.0f, EffectContext);
		if (SpecHandle.IsValid())
		{
			// 적용 전 체력 로그
			if (const UShooterAttributeSet* AttrSet = TargetASC->GetSet<UShooterAttributeSet>())
			{
				float BeforeHealth = AttrSet->GetCurrentHealth();
				UE_LOG(LogTemp, Warning, TEXT("[Grenade] %s's Health BEFORE damage: %f"), *Character->GetName(), BeforeHealth);
			}

			// 실제 데미지 적용
			TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

			// 적용 후 체력 로그
			if (const UShooterAttributeSet* AttrSet = TargetASC->GetSet<UShooterAttributeSet>())
			{
				float AfterHealth = AttrSet->GetCurrentHealth();
				UE_LOG(LogTemp, Warning, TEXT("[Grenade] %s's Health AFTER damage: %f"), *Character->GetName(), AfterHealth);
			}
		}
	}

	Destroy();
}

