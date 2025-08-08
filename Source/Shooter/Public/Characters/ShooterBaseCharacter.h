// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Character.h" // ALS 통합
#include "AlsCharacter.h" // ALS플러그인 관련 헤더파일입니다.
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "ShooterBaseCharacter.generated.h"

class UShooterAttributeSet;
class UDataAsset_StartUpDataBase;
class UShooterAbilitySystemComponent;

UCLASS()
class SHOOTER_API AShooterBaseCharacter :
	public AAlsCharacter,
	public IAbilitySystemInterface,
	public IPawnCombatInterface,
	public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface.

	//~ Begin IPawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface.

	// ~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	// ~ End IPawnUIInterface Interface.

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UShooterAbilitySystemComponent* ShooterAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UShooterAttributeSet* ShooterAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	FORCEINLINE UShooterAbilitySystemComponent* GetShooterAbilitySystemComponent() const
	{
		return ShooterAbilitySystemComponent;
	}

	FORCEINLINE UShooterAttributeSet* GetWarriorAttributeSet() const { return ShooterAttributeSet; }
};
