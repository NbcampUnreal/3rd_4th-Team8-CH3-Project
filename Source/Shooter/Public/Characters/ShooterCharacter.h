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
class UInventoryComponent;

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

	//~ Begin IPawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface.

	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UShooterUIComponent* GetShooterUIComponent() const override;
	//~ End IPawnUIInterface Interface.


protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.

#pragma region ALS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (ClampMin = 0, ForceUnits = "x"))
	float LookUpMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (ClampMin = 0, ForceUnits = "x"))
	float LookRightMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float LookUpRate{90.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float LookRightRate{240.0f};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Belica Camera")
	TObjectPtr<UAlsCameraComponent> Camera;

#pragma endregion


private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UShooterCombatComponent* ShooterCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UShooterUIComponent* ShooterUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;
#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_LookMouse(const FInputActionValue& InputActionValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);
	void Input_Walk(const FInputActionValue& InputActionValue);
	void Input_Sprint(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);
	void Input_StartFire(const FInputActionValue& InputActionValue);
	void Input_OpenIventory(const FInputActionValue& InputActionValue);
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	void Input_SwitchShoulder();
	void CalcCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void Input_Aim(const FInputActionValue& InputActionValue);
	void Input_Reload(const FInputActionValue& InputActionValue);

	void Input_EquipWeapon(const FInputActionValue& InputActionValue);
	void Input_UnequipWeapon(const FInputActionValue& InputActionValue);


#pragma endregion

	bool bIsWalking = false;
	bool bIsSprint = false;
	bool bIsJump = false;

public:
	FORCEINLINE UShooterCombatComponent* GetShooterCombatComponent() const { return ShooterCombatComponent; }
	FORCEINLINE UInventoryComponent* GetShooterInventoryComponent() const { return InventoryComponent; }
	FORCEINLINE bool IsJumping() const { return bIsJump; }
};
