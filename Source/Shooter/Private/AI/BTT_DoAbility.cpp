#include "AI/BTT_DoAbility.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

UBTT_DoAbility::UBTT_DoAbility()
{
    NodeName = "DoAbility";
}

EBTNodeResult::Type UBTT_DoAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    APawn* Pawn = AIController->GetPawn();
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    UAbilitySystemComponent* ASC = Pawn->FindComponentByClass<UAbilitySystemComponent>();
    if (!ASC)
    {
        return EBTNodeResult::Failed;
    }

    bool bActivated = ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(AbilityTag), false);

    if (bActivated)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    else
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }
}
