#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterAIController.generated.h"

UCLASS()
class SHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AShooterAIController();

	void InitBlackboardValues();
protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBlackboardComponent> BlackboardComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComp;
public:
	virtual void Tick(float DeltaSeconds) override;
};
