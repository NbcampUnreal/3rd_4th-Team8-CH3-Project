﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace ShooterGamePlayTags
{
	/** Input Tags **/
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Gamepad);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Walk);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Sprint);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Fire);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Reload);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ConsumableItem_UseItemBase);

	/** Ability Tags**/
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Equip);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Fire);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Reload);
	SHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ConsumableItem_UseItemBase);
	
}
