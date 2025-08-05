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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ConsumableItem_GrenadeItem, "InputTag.ConsumableItem.GrenadeItem");

	/** Ability Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Weapon_Equip, "Player.Ability.Weapon.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Weapon_Fire, "Player.Ability.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Weapon_Reload, "Player.Ability.Weapon.Reload");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ConsumableItem_UseItemBase, "Player.Ability.ConsumableItem.UsetItemBase");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ConsumableItem_HealingItem, "Player.Ability.ConsumableItem.HealingItem");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ConsumableItem_GrenadeItem, "Player.Ability.ConsumableItem.GrenadeItem");
	/* Shared */
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Data_ReloadAmount, "Shared.Data.ReloadAmount");
}
