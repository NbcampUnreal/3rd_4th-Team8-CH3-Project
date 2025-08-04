// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterTypes/ShooterStructTypes.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"

bool FShooterAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
