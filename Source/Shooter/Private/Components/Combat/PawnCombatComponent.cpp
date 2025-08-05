// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/ShooterWeaponBase.h"

AShooterWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	// 1. 해당 태그에 대응되는 무기 포인터를 맵에서 찾아봄
	AShooterWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet);

	// 2. 찾은 무기 포인터 반환 (더블 포인터 → 역참조)
	return FoundWeapon ? *FoundWeapon : nullptr;
}

AShooterWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	// 1. 현재 장착된 무기 태그가 유효하지 않다면 (즉, 설정되지 않았다면)
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	// 3. 유효한 태그가 있을 경우, 해당 태그로 등록된 무기를 찾아 반환
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
