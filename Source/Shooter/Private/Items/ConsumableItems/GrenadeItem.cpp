// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItems/GrenadeItem.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Items/ConsumableItems/GrenadeAttributeSet.h"
#include "Characters/ShooterCharacter.h"

AGrenadeItem::AGrenadeItem()
{
	ItemRowName = "GrenadeItem";
}

void AGrenadeItem::PickupItem(AShooterCharacter* Picker)
{
	Super::PickupItem(Picker);

	UShooterAbilitySystemComponent* PickerASC = Picker->GetShooterAbilitySystemComponent();
	if (!PickerASC)
	{
		return;
	}

	if (GrenadeAttributeSetClass)
	{
		const UAttributeSet* ExistingSet =
			PickerASC->GetAttributeSet(UGrenadeAttributeSet::StaticClass());
		if (!ExistingSet)
		{
			UGrenadeAttributeSet* GrenadeAttributeSet = NewObject<UGrenadeAttributeSet>(Picker, GrenadeAttributeSetClass);
			PickerASC->AddSpawnedAttribute(GrenadeAttributeSet);
			UE_LOG(LogTemp, Warning, TEXT("GrenadeAttributeSet Give Owner"));
		}
	}
}
