#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpec.h"
#include "BTT_DoAbility.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;

UCLASS()
class SHOOTER_API UBTT_DoAbility : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UBTT_DoAbility();

protected:
	// Ω««‡«“ Ability Tag
	UPROPERTY(EditAnywhere, Category = "GAS")
	FGameplayTag AbilityTag;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
