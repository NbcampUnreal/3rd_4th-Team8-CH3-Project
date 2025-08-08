#include "Controllers/ShooterAIController.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AShooterAIController::AShooterAIController()
{
	// AI
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        BlackboardComp->SetValueAsObject(TEXT("TargetActor"), PlayerPawn);
        SetFocus(PlayerPawn);
    }
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
    if (!InPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("OnPossess called with null Pawn!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("AI Controller %s Successfully possessed Pawn: %s"), *GetName(), *InPawn->GetName());

    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }

    if (!BlackboardComp)
    {
        UE_LOG(LogTemp, Error, TEXT("Blackboard is null!"));
        return;
    }

    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InPawn);
    if (ASC)
    {
        BlackboardComp->SetValueAsObject(TEXT("ASC"), ASC);
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
