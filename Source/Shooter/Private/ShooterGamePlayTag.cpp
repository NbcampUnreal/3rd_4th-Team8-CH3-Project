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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_OpenInventory, "InputTag.OpenInventory");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Fire, "InputTag.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Reload, "InputTag.Weapon.Reload");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ConsumableItem_UseItemBase, "InputTag.ConsumableItem.UseItemBase");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ConsumableItem_HealingItem, "InputTag.ConsumableItem.HealingItem");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ConsumableItem_GrenadeItem, "InputTag.ConsumableItem.GrenadeItem");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipWeapon, "InputTag.EquipWeapon");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipWeapon, "InputTag.UnequipWeapon");

	/** Ability Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Weapon_Equip, "Player.Ability.Weapon.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Weapon_Fire, "Player.Ability.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Weapon_Reload, "Player.Ability.Weapon.Reload");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ConsumableItem_UseItemBase, "Player.Ability.ConsumableItem.UsetItemBase");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ConsumableItem_HealingItem, "Player.Ability.ConsumableItem.HealingItem");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_ConsumableItem_GrenadeItem, "Player.Ability.ConsumableItem.GrenadeItem");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Rifle, "Player.Ability.Equip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Rifle, "Player.Ability.Unequip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack, "Player.Ability.Attack");

	/* Weapon Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Rifle, "Player.Weapon.Rifle");

	/* SetByCaller Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Shoot, "Player.SetByCaller.AttackType.Shoot");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_ChargeShoot, "Player.SetByCaller.AttackType.ChargeShoot");

	/*Event Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Rifle, "Player.Event.Equip.Rifle");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Rifle, "Player.Event.Unequip.Rifle");

	/* Shared */
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Data_ReloadAmount, "Shared.Data.ReloadAmount");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Shoot, "Shared.Event.Shoot");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_ChargeShootDamage, "Shared.SetByCaller.ChargeShootDamage");

	/* Enemy Ability Tags */
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");;

	/* Enemy Status Tags */
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
}
