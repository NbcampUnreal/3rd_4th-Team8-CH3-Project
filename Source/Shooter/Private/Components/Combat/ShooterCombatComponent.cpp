// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/ShooterCombatComponent.h"
#include "Items/Weapons/ShooterPlayerWeapon.h"

AShooterPlayerWeapon* UShooterCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	AShooterPlayerWeapon* ShooterWeapon = Cast<AShooterPlayerWeapon>(GetCharacterCurrentEquippedWeapon());

	return ShooterWeapon ? ShooterWeapon : nullptr;
}

float UShooterCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->GetShooterWeaponData().WeaponBaseDamage.GetValueAtLevel(InLevel);
}
