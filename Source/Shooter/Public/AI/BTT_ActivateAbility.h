// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ActivateAbility.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UBTT_ActivateAbility : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_ActivateAbility();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<class UGameplayAbility> AbilityToActivate;
};
