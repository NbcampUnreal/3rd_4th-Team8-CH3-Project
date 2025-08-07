// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT_ActivateAbility.h"

UBTT_ActivateAbility::UBTT_ActivateAbility()
{
    NodeName = "Activate Ability";
}

EBTNodeResult::Type UBTT_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    return EBTNodeResult::Type();
}
