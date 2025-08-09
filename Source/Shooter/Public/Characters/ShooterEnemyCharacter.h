// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterBaseCharacter.h"
#include "GameplayEffectTypes.h"
#include "ShooterEnemyCharacter.generated.h"


class UBoxComponent;
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

	UPROPERTY(EditAnywhere, Category = "Move")
	float CurWalkSpeed;

protected:
	virtual void BeginPlay() override;

	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnHealthChanged(float OldValue, float NewValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName LeftHandCollisionBoxAttachBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName RightHandCollisionBoxAttachBoneName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "combat")
	UShooterEnemyCombatComponent* ShooterEnemyCombatComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UBoxComponent* LeftHandCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UBoxComponent* RightHandCollisionBox;

	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UShooterEnemyCombatComponent* GetEnemyCombatComponent() const { return ShooterEnemyCombatComponent; }
	FORCEINLINE UBoxComponent* GetLeftHandCollisionBox() const { return LeftHandCollisionBox; }
	FORCEINLINE UBoxComponent* GetRightHandCollisionBox() const { return RightHandCollisionBox; }
};
