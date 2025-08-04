// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGamePlayTag.h"

namespace ShooterGamePlayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look_Mouse, "InputTag.Look.Mouse");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look_Gamepad, "InputTag.Look.Gamepad");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch, "InputTag.Crouch");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Walk, "InputTag.Walk");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Fire, "InputTag.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Reload, "InputTag.Weapon.Reload");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ConsumableItem_UseItemBase, "InputTag.ConsumableItem.UseItemBase");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ConsumableItem_HealingItem, "InputTag.ConsumableItem.HealingItem");

	/** Ability Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Weapon_Equip, "Ability.Player.Weapon.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Weapon_Fire, "Ability.Player.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Weapon_Reload, "Ability.Player.Weapon.Reload");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_ConsumableItem_UseItemBase, "Ability.Player.ConsumableItem.UsetItemBase");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_ConsumableItem_HealingItem, "Ability.Player.ConsumableItem.HealingItem");

	/**Data Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Data_ReloadAmount, "Data.ReloadAmount");

}
