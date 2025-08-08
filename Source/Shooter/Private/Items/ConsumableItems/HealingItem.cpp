// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItems/HealingItem.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Items/ConsumableItems/HealingItemAttributeSet.h"
#include "Characters/ShooterCharacter.h"

AHealingItem::AHealingItem()
{
	ItemRowName = "HealingItem";
}

void AHealingItem::PickupItem(AShooterCharacter* Picker)
{
	Super::PickupItem(Picker);

	UShooterAbilitySystemComponent* PickerASC = Picker->GetShooterAbilitySystemComponent();
	if (!PickerASC)
	{
		return;
	}

	if (HealingItemAttributeSetClass)
	{
		const UAttributeSet* ExistingSet =
			PickerASC->GetAttributeSet(UHealingItemAttributeSet::StaticClass());
		if (!ExistingSet)
		{
			UHealingItemAttributeSet* HealingItemAttrSet = NewObject<UHealingItemAttributeSet>(Picker, HealingItemAttributeSetClass);
			PickerASC->AddSpawnedAttribute(HealingItemAttrSet);
			UE_LOG(LogTemp, Warning, TEXT("HealingItemAttrSet Give Owner"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("HealingItemAttrSet Already Give Owner"));
		}
	}
}
