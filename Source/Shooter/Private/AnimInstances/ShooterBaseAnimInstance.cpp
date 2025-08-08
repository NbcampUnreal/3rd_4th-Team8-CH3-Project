// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ShooterBaseAnimInstance.h"
#include "ShooterFunctionLibrary.h"

bool UShooterBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UShooterFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
