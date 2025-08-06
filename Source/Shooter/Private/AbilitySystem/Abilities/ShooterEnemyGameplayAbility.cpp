// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ShooterEnemyGameplayAbility.h"
#include "Characters/ShooterEnemyCharacter.h"

AShooterEnemyCharacter* UShooterEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedShooterEnemyCharacter.IsValid())
	{
		CachedShooterEnemyCharacter = Cast<AShooterEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedShooterEnemyCharacter.IsValid() ? CachedShooterEnemyCharacter.Get() : nullptr;
}

UShooterEnemyCombatComponent* UShooterEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
