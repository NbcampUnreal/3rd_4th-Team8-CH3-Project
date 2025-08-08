#include "AI/BTS_UpdateCombatDecision.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/ShooterEnemyCharacter.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AbilitySystem/ShooterAttributeSet.h"

UBTS_UpdateCombatDecision::UBTS_UpdateCombatDecision()
{
	NodeName = "UpdateCombatDecision";

	bNotifyBecomeRelevant = true;
	bNotifyTick = true;

	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_UpdateCombatDecision, TargetActorKey), AActor::StaticClass());
	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_UpdateCombatDecision, TargetLocationKey));
}

void UBTS_UpdateCombatDecision::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	UE_LOG(LogTemp, Warning, TEXT("OnBecomeRelevant!"));
	if (AShooterBaseCharacter* ShooterEnemyChar = Cast<AShooterBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		UShooterAbilitySystemComponent* ASC = ShooterEnemyChar->GetShooterAbilitySystemComponent();
		if (ASC)
		{
			const UShooterAttributeSet* AttributeSet = ASC->GetSet<UShooterAttributeSet>();
			if (AttributeSet)
			{
				AttackRange = AttributeSet->GetAttackRange();
				UE_LOG(LogTemp, Warning, TEXT("AttackRange: %f"), AttackRange);
			}
		}
	}
}

void UBTS_UpdateCombatDecision::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	// Enemy Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UpdateTargetLocation: AIController not found."));
		return;
	}

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("UpdateTargetLocation: AIPawn not found."));
		return;
	}

	// Player Pawn
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveToTargetLocation: Player Controller not found."));
		return;
	}

	FVector PlayerLocation = PlayerPawn->GetActorLocation();

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UpdateTargetLocation: Blackboard component not found."));
		return;
	}

	BlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, PlayerPawn);
	BlackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, PlayerLocation);

	float Distance = FVector::Dist(AIPawn->GetActorLocation(), PlayerLocation);
	bool bIsInRange = AttackRange >= Distance;
	BlackboardComp->SetValueAsBool(IsInAttackRangeKey.SelectedKeyName, bIsInRange);
	UE_LOG(LogTemp, Warning, TEXT("%f > %f : %d"), Distance, AttackRange, bIsInRange);

	// ĳ���Ϳ��� ��Ŀ��
	AIController->SetFocus(PlayerPawn);
}
