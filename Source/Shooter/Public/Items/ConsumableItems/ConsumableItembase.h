// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterGamePlayTag.h"
#include "ConsumableItembase.generated.h"

class UShooterGameplayAbility;
class USphereComponent;
class AShooterCharacter;

UCLASS()
class SHOOTER_API AConsumableItembase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConsumableItembase();

    // 아이템 드랍 함수
    UFUNCTION(BlueprintCallable, Category = "Item")
    void DropItem(const FVector& DropLocation);

    UFUNCTION(BlueprintCallable, Category = "Item")
    FName GetRowName() const { return ItemRowName; }

protected:

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TMap<TSubclassOf<UShooterGameplayAbility>, FGameplayTag> ItemAbilities;

    // 오버랩 이벤트 처리 함수
    UFUNCTION()
    void OnOverlapCheckBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    void MoveToCharacter(AShooterCharacter* Player);

    // 오버랩 이벤트 처리 함수
    UFUNCTION()
    void OnPickupCheckBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    virtual void PickupItem(AShooterCharacter* Picker);

    UFUNCTION(BlueprintCallable, Category = "ConsumableItem")
    void GiveAbilityToOwner(AShooterCharacter* NewOwner);

    // 오버랩 콜리전용 Sphere 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Collision")
    USphereComponent* OverlapCheckCollision;

    // 슥듭용 Sphere 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Collision")
    USphereComponent* PickupCheckCollision;

    // 아이템 외형 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Mesh")
    UStaticMeshComponent* ItemMesh;

    UPROPERTY(EditAnywhere, Category = "Item")
    int32 PlusItemCount = 1;

    UPROPERTY(EditAnywhere, Category = "Item")
    FName ItemRowName;
    virtual void Tick(float DeltaTime) override;

private:
    AShooterCharacter* TargetCharacter;

    FVector TargetLocation;

    bool bIsMovingToPlayer = false;

    UPROPERTY(EditAnywhere, Category = "Item")
    float MoveSpeed = 3.f;

    
};
