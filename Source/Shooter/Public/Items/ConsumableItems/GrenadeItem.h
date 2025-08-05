// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ConsumableItems/ConsumableItembase.h"
#include "GrenadeItem.generated.h"

class UGrenadeAttributeSet;
/**
 * 
 */
UCLASS()
class SHOOTER_API AGrenadeItem : public AConsumableItembase
{
	GENERATED_BODY()

public:
	AGrenadeItem();

protected:
	void PickupItem(AShooterCharacter* Picker) override;

	// 선택 가능한 AttributeSet 클래스 (블루프린트에서 지정)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|GAS")
	TSubclassOf<UGrenadeAttributeSet> GrenadeAttributeSetClass;
};
