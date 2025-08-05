// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ShooterPlayerGameplayAbility.h"
#include "Characters/ShooterCharacter.h"
#include "Controllers/ShooterController.h"

/**
 * @brief ActorInfo에서 AShooterCharacter를 가져오고, 이를 캐시에 저장하여 반환하는 함수입니다.
 *
 * 1. 캐시된 캐릭터가 유효하지 않을 경우(최초 접근 또는 이미 파괴된 경우) ActorInfo에서 AvatarActor를 가져와 AShooterCharacter로 캐스팅하고 캐시에 저장합니다.
 * 2. 캐시된 캐릭터가 유효하면 이를 반환하고, 무효하거나 존재하지 않으면 nullptr을 반환합니다.
 *
 * @return 캐시된 AShooterCharacter 포인터. 유효하지 않은 경우 nullptr을 반환합니다.
 */
AShooterCharacter* UShooterPlayerGameplayAbility::GetShooterCharacterFromActorInfo()
{
	if (!CachedShooterCharacter.IsValid())
	{
		CachedShooterCharacter = Cast<AShooterCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedShooterCharacter.IsValid() ? CachedShooterCharacter.Get() : nullptr;
}

/**
 * @brief ActorInfo에서 AShooterController를 가져오고, 이를 캐시에 저장하여 반환하는 함수입니다.
 *
 *	1. 캐시된 컨트롤러가 유효하지 않을 경우(최초 접근 또는 이미 파괴된 경우) ActorInfo에서 PlayerController를 가져와 AShooterController로 캐스팅하고 캐시에 저장합니다.
 *	2. 캐시된 컨트롤러가 유효하면 이를 반환하고, 무효하거나 존재하지 않으면 nullptr을 반환합니다.
 *
 * @return 캐시된 AShooterController 포인터. 유효하지 않은 경우 nullptr을 반환합니다.
 */
AShooterController* UShooterPlayerGameplayAbility::GetShooterControllerFromActorInfo()
{
	if (CachedShooterController.IsValid())
	{
		CachedShooterController = Cast<AShooterController>(CurrentActorInfo->PlayerController);
	}
	return CachedShooterController.IsValid() ? CachedShooterController.Get() : nullptr;
}

UShooterCombatComponent* UShooterPlayerGameplayAbility::GetShooterCombatComponentFromActorInfo()
{
	const AShooterCharacter* ShooterCharacter = GetShooterCharacterFromActorInfo();
	return ShooterCharacter ? ShooterCharacter->GetShooterCombatComponent() : nullptr;
}
