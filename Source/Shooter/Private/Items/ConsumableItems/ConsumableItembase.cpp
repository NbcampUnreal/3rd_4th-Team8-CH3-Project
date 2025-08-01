// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItems/ConsumableItembase.h"
#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Characters/ShooterCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AConsumableItembase::AConsumableItembase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
    RootComponent = ItemMesh;

    OverlapCheckCollision = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapCheckCollision"));
    OverlapCheckCollision->InitSphereRadius(1000.f);
    OverlapCheckCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // 오버랩 가능하게 설정
    OverlapCheckCollision->SetupAttachment(RootComponent);

    OverlapCheckCollision->OnComponentBeginOverlap.AddDynamic(this, &AConsumableItembase::OnOverlapCheckBegin);

    PickupCheckCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCheckCollision"));
    PickupCheckCollision->InitSphereRadius(100.f);
    PickupCheckCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // 오버랩 가능하게 설정
    PickupCheckCollision->SetupAttachment(RootComponent);

    PickupCheckCollision->OnComponentBeginOverlap.AddDynamic(this, &AConsumableItembase::OnPickupCheckBegin);
}

//적이 죽을 때 해당 위치에 아이템 드랍
//적이 새로운 아이템을 월드에 스폰하고 해당 아이템의 DropItem 호출
void AConsumableItembase::DropItem(const FVector& DropLocation)
{
    SetActorLocation(DropLocation);
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);

    //필요시 요소 추가(파티클, 오디오)
}

void AConsumableItembase::BeginPlay()
{
    Super::BeginPlay();
    SetActorTickEnabled(false);
    UE_LOG(LogTemp, Warning, TEXT("Tick Enabled: %s"), IsActorTickEnabled() ? TEXT("true") : TEXT("false"));
}

void AConsumableItembase::OnOverlapCheckBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("OvelapCheck"));
    AShooterCharacter* ShooterPlayer = Cast<AShooterCharacter>(OtherActor);
    if (!ShooterPlayer) return;
    
    MoveToCharacter(ShooterPlayer);

}

void AConsumableItembase::MoveToCharacter(AShooterCharacter* Player)
{
    UE_LOG(LogTemp, Warning, TEXT("MoveToCharacter"));
    if (!Player) return;
    SetActorTickEnabled(true); // 이동 시작 시 Tick 활성화
    TargetLocation = Player->GetActorLocation();
    bIsMovingToPlayer = true;
    UE_LOG(LogTemp, Warning, TEXT("Tick Enabled: %s"), IsActorTickEnabled() ? TEXT("true") : TEXT("false"));
}

void AConsumableItembase::OnPickupCheckBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("PickupCheck"));
    AShooterCharacter* ShooterPlayer = Cast<AShooterCharacter>(OtherActor);
    if (!ShooterPlayer) return;

    PickupItem(ShooterPlayer);
}

void AConsumableItembase::PickupItem(AShooterCharacter* Picker)
{
    UE_LOG(LogTemp, Warning, TEXT("PickupItem"));
    bIsMovingToPlayer = false;
    SetActorTickEnabled(false);

    if (!Picker) return;
    //인벤토리 작업 후 로직 수정 예정
    /*
    TSubclassOf<AConsumableItembase> ComsumableItemClass = GetClass();
    if (Picker->TestInventoryMap.Contains(ComsumableItemClass))
    {
        Picker->TestInventoryMap[ComsumableItemClass] = Picker->TestInventoryMap[ComsumableItemClass] + PlusItemCount;
    }
    else
    {
        Picker->TestInventoryMap.Add(ComsumableItemClass, PlusItemCount);
        GiveAbilityToOwner(Picker);
    }
    */
    
    Destroy(); // 아이템 제거
}

void AConsumableItembase::GiveAbilityToOwner(AShooterCharacter* NewOwner)
{
    if (!NewOwner) return;

    UShooterAbilitySystemComponent* OwnerASC = NewOwner->GetShooterAbilitySystemComponent();
    if (!OwnerASC) return;

    for (const auto& Pair : ItemAbilities)
    {
        TSubclassOf<UShooterGameplayAbility> AbilityClass = Pair.Key;
        FGameplayTag InputTag = Pair.Value;

        if (AbilityClass && OwnerASC->GetOwner()->HasAuthority())
        {
            FGameplayAbilitySpec Spec(AbilityClass, 1);
            Spec.GetDynamicSpecSourceTags().AddTag(InputTag);
            OwnerASC->GiveAbility(Spec);

            UE_LOG(LogTemp, Warning, TEXT("Ability given: %s with tag: %s"), *AbilityClass->GetName(), *InputTag.ToString());
        }
    }
}

void AConsumableItembase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
    if (bIsMovingToPlayer)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);

        SetActorLocation(NewLocation);
    }
}
