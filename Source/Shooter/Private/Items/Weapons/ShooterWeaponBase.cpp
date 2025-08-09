// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ShooterWeaponBase.h"

#include "ShooterFunctionLibrary.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Items/Weapons/WeaponAttributeSet.h"
#include "ShooterGamePlayTag.h"
#include "Characters/ShooterBaseCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
AShooterWeaponBase::AShooterWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(RootComponent);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void AShooterWeaponBase::GiveAbilityToOwner(AActor* NewOwner)
{
	if (!NewOwner)
	{
		return;
	}

	AShooterBaseCharacter* OwnwerCharacter = Cast<AShooterBaseCharacter>(NewOwner);
	if (!OwnwerCharacter)
	{
		return;
	}

	UShooterAbilitySystemComponent* OwnerASC = OwnwerCharacter->GetShooterAbilitySystemComponent();
	if (!OwnerASC)
	{
		return;
	}

	for (const auto& Pair : WeaponAbilityMap)
	{
		TSubclassOf<UShooterGameplayAbility> AbilityClass = Pair.Key;
		FGameplayTag InputTag = Pair.Value;

		if (AbilityClass && OwnerASC->GetOwner()->HasAuthority())
		{
			FGameplayAbilitySpec Spec(AbilityClass, 1, INDEX_NONE, OwnerASC);
			Spec.GetDynamicSpecSourceTags().AddTag(InputTag);
			OwnerASC->GiveAbility(Spec);

			UE_LOG(LogTemp, Warning, TEXT("Ability given: %s with tag: %s"), *AbilityClass->GetName(),
			       *InputTag.ToString());
		}
	}

	if (WeaponAttributeSetClass)
	{
		UWeaponAttributeSet* WeaponAttrSet = NewObject<UWeaponAttributeSet>(NewOwner, WeaponAttributeSetClass);
		OwnerASC->AddSpawnedAttribute(WeaponAttrSet);

		UE_LOG(LogTemp, Warning, TEXT("WeaponAttrSet Give Owner"));
	}
}

void AShooterWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 무기를 소유한 캐릭터를 가져옴 (보통 무기를 들고 있는 플레이어)
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("무기의 소유 폰을 instigator로 설정하는 걸 잊었습니다: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UShooterFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void AShooterWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 무기를 소유한 캐릭터를 가져옴 (보통 무기를 들고 있는 플레이어)
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("무기의 소유 폰을 instigator로 설정하는 걸 잊었습니다: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UShooterFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}
