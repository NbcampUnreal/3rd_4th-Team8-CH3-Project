// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "ShooterCharacter.generated.h"

class UAlsCameraComponent;
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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Belica Camera")
	TObjectPtr<UAlsCameraComponent> Camera;


private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UShooterCombatComponent* ShooterCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UShooterUIComponent* ShooterUIComponent;


#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Reload(const FInputActionValue& InputActionValue);
	void Input_LookMouse(const FInputActionValue& InputActionValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);
	void Input_Walk(const FInputActionValue& InputActionValue);
	void Input_Sprint(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);
	void Input_StartFire(const FInputActionValue& InputActionValue);
	void Input_StopFire(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	void Input_OnSwitchShoulder();
	void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& Unused, float& VerticalLocation);
	void CalcCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);

	bool IsInputPressed(const FInputActionValue& InputActionValue);

	void SetMaxWalkSpeed(const float NewMaxWalkSpeed);
	void Input_EquipWeapon(const FInputActionValue& InputActionValue);
	void Input_UnequipWeapon(const FInputActionValue& InputActionValue);


#pragma endregion

	bool bIsWalking = false;
	bool bIsSprint = false;
	bool bIsJump = false;

	

public:
	FORCEINLINE UShooterCombatComponent* GetShooterCombatComponent() const { return ShooterCombatComponent; }
	FORCEINLINE bool IsJumping() const { return bIsJump; }
};
