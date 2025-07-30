// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ShooterWeaponBase.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "Items/Weapons/WeaponAttributeSet.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Characters/ShooterBaseCharacter.h"


// Sets default values
AShooterWeaponBase::AShooterWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShooterWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}

void AShooterWeaponBase::GiveAbilityToOwner(AActor* NewOwner)
{
	if (!NewOwner) return;
	OwnerActor = NewOwner;
	AShooterBaseCharacter* OwnwerCharacter = Cast<AShooterBaseCharacter>(NewOwner);

	OwnerASC = OwnwerCharacter->GetShooterAbilitySystemComponent();

	if (!OwnerASC) return;

	auto Give = [&](TSubclassOf<UGameplayAbility> AbilityClass, FGameplayTag InputTag)
		{
			if (AbilityClass && OwnerASC->GetOwner()->HasAuthority())
			{
				FGameplayAbilitySpec Spec(AbilityClass, 1);

				// InputTag를 Spec의 DynamicAbilityTags에 추가
				Spec.DynamicAbilityTags.AddTag(InputTag);

				OwnerASC->GiveAbility(Spec);

				UE_LOG(LogTemp, Warning, TEXT("Ability given: %s with tag: %s"), *AbilityClass->GetName(), *InputTag.ToString());
			}
		};

	Give(FireAbilityClass, ShooterGamePlayTags::InputTag_Weapon_Fire);
	Give(ReloadAbilityClass, ShooterGamePlayTags::InputTag_Weapon_Reload);
	if (WeaponAttributeSetClass)
	{
		UWeaponAttributeSet* WeaponAttrSet = NewObject<UWeaponAttributeSet>(OwnerActor, WeaponAttributeSetClass);
		OwnerASC->AddSpawnedAttribute(WeaponAttrSet);
		UE_LOG(LogTemp, Warning, TEXT("WeaponAttrSet Good"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AbilityGive"));
}

