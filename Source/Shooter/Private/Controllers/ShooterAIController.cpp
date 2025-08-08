#include "Controllers/ShooterAIController.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AShooterAIController::AShooterAIController()
{
	// AI
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	// 팀 ID 설정
	SetGenericTeamId(FGenericTeamId(1));
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	// �������� �� �ʱ�ȭ
	if (!BlackboardComp)
	{
	}
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller %s Successfully possessed Pawn: %s"), *GetName(), *InPawn->GetName());
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
