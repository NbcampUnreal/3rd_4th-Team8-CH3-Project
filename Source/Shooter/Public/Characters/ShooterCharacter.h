// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AlsCharacter.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "GameplayTagContainer.h"
#include "ShooterCharacter.generated.h"

class UAlsCameraComponent;
class UCameraComponent;
class USpringArmComponent;
class UDataAsset_InputConfig;
class UShooterCombatComponent;
class UShooterUIComponent;
class UInventoryComponent;
class UShooterAbilitySystemComponent;
class UShooterAttributeSet;
class UDataAsset_StartUpDataBase;
class UAbilitySystemComponent;

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterCharacter :
	public AAlsCharacter,
	public IAbilitySystemInterface,
	public IPawnCombatInterface,
	public IPawnUIInterface
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

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.


	// 화랑님 요청
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	// 화랑님 요청
	
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UShooterAbilitySystemComponent* ShooterAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UShooterAttributeSet* ShooterAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UShooterCombatComponent* ShooterCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UShooterUIComponent* ShooterUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;
#pragma endregion

#pragma region Inputs
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Roll();
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

	void Input_EquipWeapon();
	void Input_UnequipWeapon();


#pragma endregion

	bool bIsWalking = false;
	bool bIsSprint = false;
	bool bIsJump = false;

public:
	FORCEINLINE UShooterCombatComponent* GetShooterCombatComponent() const { return ShooterCombatComponent; }
	FORCEINLINE UInventoryComponent* GetShooterInventoryComponent() const { return InventoryComponent; }
	FORCEINLINE bool IsJumping() const { return bIsJump; }
};
