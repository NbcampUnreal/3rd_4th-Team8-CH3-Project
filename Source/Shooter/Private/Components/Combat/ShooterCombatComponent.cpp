// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/ShooterCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Items/Weapons/ShooterPlayerWeapon.h"

void UShooterCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// 공격때마다 1회만 공격처리
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		ShooterGamePlayTags::Shared_Event_Shoot,
		EventData
	);
}

void UShooterCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractingActor)
{
}

AShooterPlayerWeapon* UShooterCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	AShooterPlayerWeapon* ShooterWeapon = Cast<AShooterPlayerWeapon>(GetCharacterCurrentEquippedWeapon());

	return ShooterWeapon ? ShooterWeapon : nullptr;
}

AShooterPlayerWeapon* UShooterCombatComponent::GetShooterCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AShooterPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

float UShooterCombatComponent::GetShooterCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->ShooterWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}
