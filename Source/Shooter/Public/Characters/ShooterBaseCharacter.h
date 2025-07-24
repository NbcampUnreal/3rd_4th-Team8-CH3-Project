// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ShooterBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UShooterAbilitySystemComponent;

UCLASS()
class SHOOTER_API AShooterBaseCharacter :
	public ACharacter,
	public IAbilitySystemInterface

{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface.

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UShooterAbilitySystemComponent* ShooterAbilitySystemComponent;

public:
	FORCEINLINE UShooterAbilitySystemComponent* GetShooterAbilitySystemComponent() const
	{
		return ShooterAbilitySystemComponent;
	}
};
