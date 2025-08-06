// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "ShooterCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDataAsset_InputConfig;
class UShooterCombatComponent;
class UShooterUIComponent;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterCharacter : public AShooterBaseCharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyCategory")
	TSubclassOf<class AActor> MyBlueprintClass;

#pragma region ALS
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ALS|Settings")
	TObjectPtr<UAlsCharacterSettings> AlsCharacterSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ALS|Settings")
	TObjectPtr<UAlsMovementSettings> AlsMovementSettings;
#pragma endregion

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UShooterCombatComponent* ShooterCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UShooterUIComponent* ShooterUIComponent;


#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);
	void Input_Walk(const FInputActionValue& InputActionValue);
	void Input_Sprint(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

	bool IsInputPressed(const FInputActionValue& InputActionValue);

	void SetMaxWalkSpeed(const float NewMaxWalkSpeed);


#pragma endregion

	bool bIsWalking = false;
	bool bIsSprint = false;
	bool bIsJump = false;

	

public:
	FORCEINLINE UShooterCombatComponent* GetShooterCombatComponent() const { return ShooterCombatComponent; }
	FORCEINLINE bool IsJumping() const { return bIsJump; }
};
