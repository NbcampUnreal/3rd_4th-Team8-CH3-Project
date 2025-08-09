#include "Controllers/ShooterAIController.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AbilitySystemComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AShooterAIController::AShooterAIController()
{
	// AI
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemySenseConfig_Sight"));

	if (AISenseConfig_Sight)
	{
		// '적'으로 설정된 대상을 감지하도록 설정
		AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
		// '아군'으로 설정된 대상은 감지하지 않도록 설정
		AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
		// '중립'으로 설정된 대상은 감지하지 않도록 설정
		AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

		AISenseConfig_Sight->SightRadius = 3200.f;
		// 대상을 한 번 놓쳤을 때, 시야를 완전히 잃게 되는 추가 반경을 0으로 설정 (즉, 기본 시야 반경을 벗어나면 바로 잃는다.)
		AISenseConfig_Sight->LoseSightRadius = 3500.f;
		AISenseConfig_Sight->PeripheralVisionAngleDegrees = 90.f;
	}

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	if (PerceptionComponent)
	{
		PerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
		PerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
		// UAISense_Sight
		// 인지 시스템이 대상을 감지하거나 잃을 때마다 'OnEnemyPerceptionUpdated' 함수를 호출하도록 연결(바인딩)
		PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);
	}
	// 팀 ID 설정
	SetGenericTeamId(FGenericTeamId(1));
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
	if (InPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller %s Successfully possessed Pawn: %s"), *GetName(), *InPawn->GetName());
	}

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}

	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Blackboard is null!"));
		return;
	}
}

/**
 * @brief 다른 액터에 대한 이 AI의 팀 태도를 결정합니다.
 * @param Other 태도를 확인할 다른 액터입니다.
 * @return ETeamAttitude::Type 팀 태도를 반환합니다. (Hostile, Friendly, Neutral)
 */

ETeamAttitude::Type AShooterAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);

	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnToCheck->GetController());

	// 적 인지
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;
}

/**
 * @brief AI 인지 시스템에 의해 타겟의 인지 정보가 업데이트될 때 호출되는 콜백 함수입니다.
 * @param Actor 인지된 액터입니다.
 * @param Stimulus 인지 자극에 대한 정보입니다.
 */
void AShooterAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// 인지된 액터가 유효하고, 성공적으로 '감지'되었는지 확인
	if (Actor && Stimulus.WasSuccessfullySensed())
	{
		// 블랙보드에 'TargetActor' 키로 감지된 액터를 설정
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), Actor);
			// AI가 항상 타겟을 바라보도록 포커스를 설정
			SetFocus(Actor);
		}
	}
	else
	{
		// 만약 타겟을 '잃었다면' (Stimulus가 성공적이지 않다면), 블랙보드 값을 비움.
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			BlackboardComponent->ClearValue(TEXT("TargetActor"));
			// 포커스를 해제.
			ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
