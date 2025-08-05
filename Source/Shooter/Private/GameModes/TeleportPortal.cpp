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
	TrigerZone->InitSphereRadius(150.0f);
	TrigerZone->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(Root);

	//5부터 0까지가 아니고 6부터 1까지 계산 카운트다운 54321
	CountTime = 6;

}

void ATeleportPortal::BeginPlay()
{
	Super::BeginPlay();

	TrigerZone->OnComponentBeginOverlap.AddDynamic(this, &ATeleportPortal::OnOverlapBegin);
	TrigerZone->OnComponentEndOverlap.AddDynamic(this, &ATeleportPortal::OnOverlapEnd);
	UE_LOG(LogTemp, Warning, TEXT("Create Portal"));
	
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

	if (OtherActor == OverlapActor)
	{
		GetWorldTimerManager().ClearTimer(PortalTimerHandle);
		OverlapActor = nullptr;
		CountTime = 6;
		UE_LOG(LogTemp, Warning, TEXT("Player left portal zone. Timer cancelled."));
	}
}

void ATeleportPortal::TeleportHandle()
{
	CountTime--;

	//UI 카운트다운 시간 초 전달 부분 예정
	UE_LOG(LogTemp, Warning, TEXT("CountDown : %d"), CountTime);

	if (CountTime <= 1) {
		GetWorldTimerManager().ClearTimer(PortalTimerHandle);

		UShooterGameInstance* GI = Cast<UShooterGameInstance>(GetGameInstance());
		if (GI)
		{
			GI->LoadWaveLevel();
			Destroy();
		}
	}

	
}

