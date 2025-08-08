// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ShooterWeaponBase.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Items/Weapons/WeaponAttributeSet.h"
#include "ShooterGamePlayTag.h"
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
