// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ShooterPlayerWeapon.h"

void AShooterPlayerWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AShooterPlayerWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}

// const FWarriorHeroWeaponData& AShooterPlayerWeapon::GetShooterWeaponData() const
// {
// 	return ShooterWeaponData;
// }
