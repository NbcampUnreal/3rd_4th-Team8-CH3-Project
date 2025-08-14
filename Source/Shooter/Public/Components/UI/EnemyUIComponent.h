// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class AShooterEnemyCharacter;
    // 보스 UI Spawn 알림 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawned, AShooterEnemyCharacter*, EnemyActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDead, AShooterEnemyCharacter*, EnemyActor);
/**
 * 
 */
UCLASS()
class SHOOTER_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:


    UPROPERTY(BlueprintAssignable, Category = "UI|Boss")
    FOnEnemySpawned OnEnemyUISpawned;

    UPROPERTY(BlueprintAssignable, Category = "UI|Boss")
    FOnEnemyDead OnEnemyUIDead;

    UFUNCTION(BlueprintCallable, Category = "UI|Boss")
    void BroadcastEnemyUIDead(AShooterEnemyCharacter* EnemyActor);

};
