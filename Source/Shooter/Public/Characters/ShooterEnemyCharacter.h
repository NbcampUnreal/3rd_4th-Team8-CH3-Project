// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterBaseCharacter.h"
#include "GameplayEffectTypes.h"
#include "ShooterEnemyCharacter.generated.h"


class UWidgetComponent;
class UDataAsset_InputConfig;
class AAIController;
class UShooterEnemyCombatComponent;
class UBehaviorTree;
/**
 *
 */
UCLASS()
class SHOOTER_API AShooterEnemyCharacter : public AShooterBaseCharacter
{
	GENERATED_BODY()

public:
	AShooterEnemyCharacter();
	//~ Begin IPawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface.

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	//~ End IPawnUIInterface Interface.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, Category = "Move")
	float CurWalkSpeed;

	UPROPERTY(EditAnywhere, Category = "AttackRange")
	float AttackRange;

protected:
	virtual void BeginPlay() override;

	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnHealthChanged(float OldValue, float NewValue);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "combat")
	UShooterEnemyCombatComponent* ShooterEnemyCombatComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UShooterEnemyCombatComponent* GetEnemyCombatComponent() const { return ShooterEnemyCombatComponent; }
};
