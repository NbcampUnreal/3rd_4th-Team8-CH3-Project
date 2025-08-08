#include "GameModes/TeleportPortal.h"
#include "Components/SphereComponent.h"
#include "Characters/ShooterCharacter.h"
#include "GameModes/ShooterGameInstance.h"


ATeleportPortal::ATeleportPortal()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TrigerZone = CreateDefaultSubobject<USphereComponent>(TEXT("TrigerZone"));
	TrigerZone->SetupAttachment(Root);
	TrigerZone->InitSphereRadius(190.0f);
	TrigerZone->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(Root);

	CountDownTimer = 5;
}

void ATeleportPortal::BeginPlay()
{
	Super::BeginPlay();

	TrigerZone->OnComponentBeginOverlap.AddDynamic(this, &ATeleportPortal::OnOverlapBegin);
	TrigerZone->OnComponentEndOverlap.AddDynamic(this, &ATeleportPortal::OnOverlapEnd);
	UE_LOG(LogTemp, Warning, TEXT("Create Portal"));


	CountTime = CountDownTimer;
	
}


void ATeleportPortal::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	
	if (OtherActor && OtherActor->IsA<AShooterCharacter>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Overlap portal zone. Timer Start."));
		OverlapActor = OtherActor;

		OnPlayerInPortal.Broadcast();
		OnCountDown.Broadcast(CountTime);
		UE_LOG(LogTemp, Warning, TEXT("CountDown : %d"), CountTime);

		GetWorldTimerManager().SetTimer(
			PortalTimerHandle,
			this,
			&ATeleportPortal::TeleportHandle,
			1.0f,
			true
		);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not ShooterCharacter : %s"), *OtherActor->GetClass()->GetName());
	}
}


void ATeleportPortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnPlayerOutPortal.Broadcast();

	if (OtherActor && OtherActor == OverlapActor)
	{
		ResetPortalState();
	}
}

void ATeleportPortal::ResetPortalState()
{
	GetWorldTimerManager().ClearTimer(PortalTimerHandle);
	OverlapActor = nullptr;
	CountTime = CountDownTimer;
	UE_LOG(LogTemp, Warning, TEXT("Player left portal zone. Timer cancelled."));
}

void ATeleportPortal::TeleportHandle()
{
	CountTime--;

	OnCountDown.Broadcast(CountTime);
	UE_LOG(LogTemp, Warning, TEXT("CountDown : %d"), CountTime);

	if (CountTime <= 0) {
		GetWorldTimerManager().ClearTimer(PortalTimerHandle);

		UShooterGameInstance* GI = Cast<UShooterGameInstance>(GetGameInstance());
		if (GI)
		{
			OnDestroyPortal.Broadcast();
			GI->LoadWaveLevel();
			Destroy();
		}
	}	
}
