// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Projectile/GrenadeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/ShooterBaseCharacter.h"
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
}

void AGrenadeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		AShooterBaseCharacter* HitCharacter = Cast<AShooterBaseCharacter>(OtherActor);
		if (HitCharacter)
		{
			OnExplosion();
		}
	}
}

void AGrenadeProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AShooterBaseCharacter* BaseChar = Cast<AShooterBaseCharacter>(OtherActor))
	{
		if (!OverlappingCharacters.Contains(BaseChar))
		{
			OverlappingCharacters.Add(BaseChar);
			UE_LOG(LogTemp, Log, TEXT("OnOverlapBegin: Added %s to OverlappingCharacters"), *BaseChar->GetName());
		}
	}
}

void AGrenadeProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AShooterBaseCharacter* BaseChar = Cast<AShooterBaseCharacter>(OtherActor))
	{
		if (OverlappingCharacters.Contains(BaseChar))
		{
			OverlappingCharacters.Remove(BaseChar);
			UE_LOG(LogTemp, Log, TEXT("OnOverlapEnd: Removed %s from OverlappingCharacters"), *BaseChar->GetName());
		}
	}
}

void AGrenadeProjectile::OnExplosion()
{
	GetWorldTimerManager().ClearTimer(ExplosionTimerHandle);

	UE_LOG(LogTemp, Warning, TEXT("[Grenade] OnExplosion called"));

	for (AShooterBaseCharacter* Character : OverlappingCharacters)
	{
		if (!Character)
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

		FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		if (InstigatorCharacter)
		{
			EffectContext.AddInstigator(InstigatorCharacter, InstigatorCharacter);
		}

		// Spec 생성
		FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageGameplayEffect, 1.0f, EffectContext);
		if (SpecHandle.IsValid())
		{
			// GE 적용 전: 체력 확인
			if (const UShooterAttributeSet* AttrSet = TargetASC->GetSet<UShooterAttributeSet>())
			{
				float BeforeHealth = AttrSet->GetCurrentHealth();
				UE_LOG(LogTemp, Warning, TEXT("[Grenade] %s's Health BEFORE damage: %f"), *Character->GetName(), BeforeHealth);
			}

			// GE 적용
			TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

			// GE 적용 후: 체력 확인
			if (const UShooterAttributeSet* AttrSet = TargetASC->GetSet<UShooterAttributeSet>())
			{
				float AfterHealth = AttrSet->GetCurrentHealth();
				UE_LOG(LogTemp, Warning, TEXT("[Grenade] %s's Health AFTER damage: %f"), *Character->GetName(), AfterHealth);
			}
		}
	}

	Destroy();
}