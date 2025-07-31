// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WeaponAttributeSet.h"

UWeaponAttributeSet::UWeaponAttributeSet()
{
    InitMaxAmmo(30.f);
    InitCurrentAmmo(GetMaxAmmo());
}

