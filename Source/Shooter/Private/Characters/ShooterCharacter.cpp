// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ShooterGamePlayTag.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Components/Input/ShooterInputComponent.h"
#include "Components/Combat/ShooterCombatComponent.h"
#include "Components/UI/ShooterUIComponent.h"
#include "DataAssets/StartUpDatas/DataAsset_StartUpDataBase.h"
#include "AlsCharacter.h"
#include "ALSCamera/Public/AlsCameraComponent.h"
#include "Utility/AlsGameplayTags.h"
#include "Utility/AlsVector.h"

AShooterCharacter::AShooterCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false; // ALS 요구사항에 맞게 수정 true -> False
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	ShooterCombatComponent = CreateDefaultSubobject<UShooterCombatComponent>(TEXT("ShooterCombatComponent"));
	ShooterUIComponent = CreateDefaultSubobject<UShooterUIComponent>(TEXT("ShooterUIComponent"));

	Camera = CreateDefaultSubobject<UAlsCameraComponent>(FName{TEXTVIEW("Camera")});
	Camera->SetupAttachment(GetMesh());
	Camera->SetRelativeRotation_Direct({0.0f, 90.0f, 0.0f});
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset이 비어있습니다."))

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	if (!PlayerInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInputComponent is null!"));
		return;
	}
	
	UShooterInputComponent* ShooterInputComponent = Cast<UShooterInputComponent>(PlayerInputComponent); // error

	if (!ShooterInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ShooterInputComponent is null!"));
		return;
	}
	
#pragma region InputBinding // ??? wtf 외안되여!??
	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Move,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Move
		);
	
	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Look_Mouse,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_LookMouse
		);
	
	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Jump,
		ETriggerEvent::Started,
		this,
		&ThisClass::Input_Jump
		);
	
	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Crouch,
		ETriggerEvent::Started,
		this,
		&ThisClass::Input_Crouch
		);
	
	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Walk,
		ETriggerEvent::Started,
		this,
		&ThisClass::Input_Walk
		);
	
	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Sprint,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Sprint
		);

	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Weapon_Fire,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_StartFire
		);

	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Weapon_Reload,
		ETriggerEvent::Started,
		this,
		&ThisClass::Input_Reload
		);

	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Weapon_EquipWeapon,
		ETriggerEvent::Started,
		this,
		&ThisClass::Input_EquipWeapon
		);
	
	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Weapon_UnequipWeapon,
		ETriggerEvent::Started,
		this,
		&ThisClass::Input_UnequipWeapon
		);

	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Weapon_Aim,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Aim
		);

	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_SwitchShoulder,
		ETriggerEvent::Started,
		this,
		&ThisClass::Input_SwitchShoulder
		);

	ShooterInputComponent->BindAbilityInputAction(
		InputConfigDataAsset,
		this,
		&ThisClass::Input_AbilityInputPressed,
		&ThisClass::Input_AbilityInputReleased
	);
}
#pragma endregion

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(ShooterAbilitySystemComponent);
		}
	}
}
#pragma region InputMoving
void AShooterCharacter::Input_Sprint(const FInputActionValue& InputActionValue)
{
	SetDesiredGait(InputActionValue.Get<bool>() ? AlsGaitTags::Sprinting : AlsGaitTags::Running);
}

void AShooterCharacter::Input_Walk(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Walk!!"));
	if (GetDesiredGait() == AlsGaitTags::Walking)
	{
		SetDesiredGait(AlsGaitTags::Running);
	}
	else if (GetDesiredGait() == AlsGaitTags::Running)
	{
		SetDesiredGait(AlsGaitTags::Walking);
	}
}

void AShooterCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	if (InputActionValue.Get<bool>())
	{
		if (StopRagdolling())
		{
			return;
		}

		if (StartMantlingGrounded())
		{
			return;
		}

		if (GetStance() == AlsStanceTags::Crouching)
		{
			SetDesiredStance(AlsStanceTags::Standing);
			return;
		}

		Jump();
	}
	else
	{
		StopJumping();
	}
}

void AShooterCharacter::Input_Crouch(const FInputActionValue& InputActionValue)
{
	if (GetDesiredStance() == AlsStanceTags::Standing)
	{
		SetDesiredStance(AlsStanceTags::Crouching);
	}
	else if (GetDesiredStance() == AlsStanceTags::Crouching)
	{
		SetDesiredStance(AlsStanceTags::Standing);
	}
}

void AShooterCharacter::Input_Move(const FInputActionValue& ActionValue)
{
	const auto Value{UAlsVector::ClampMagnitude012D(ActionValue.Get<FVector2D>())};

	auto ViewRotation{GetViewState().Rotation};

	if (IsValid(GetController()))
	{
		FVector ViewLocation;
		GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}

	const auto ForwardDirection{UAlsVector::AngleToDirectionXY(UE_REAL_TO_FLOAT(ViewRotation.Yaw))};
	const auto RightDirection{UAlsVector::PerpendicularCounterClockwiseXY(ForwardDirection)};

	AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void AShooterCharacter::Input_LookMouse(const FInputActionValue& ActionValue)
{
	const FVector2f Value{ActionValue.Get<FVector2D>()};

	AddControllerPitchInput(Value.Y * LookUpMouseSensitivity);
	AddControllerYawInput(Value.X * LookRightMouseSensitivity);
}

void AShooterCharacter::Input_SwitchShoulder()
{
	Camera->SetRightShoulder(!Camera->IsRightShoulder());
}

void AShooterCharacter::CalcCamera(const float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	if (Camera->IsActive())
	{
		Camera->GetViewInfo(ViewInfo);
		return;
	}

	Super::CalcCamera(DeltaTime, ViewInfo);
}
#pragma endregion

#pragma region Weapon
void AShooterCharacter::Input_Aim(const FInputActionValue& InputActionValue)
{
	if (GetOverlayMode() == AlsOverlayModeTags::Rifle)
	{
		SetDesiredAiming(InputActionValue.Get<bool>());
	}else if (GetOverlayMode() != AlsOverlayModeTags::Rifle)
	{
		UE_LOG(LogTemp, Warning, TEXT("You Can Aiming only Hold Waepon"));
	}
}

void AShooterCharacter::Input_Reload(const FInputActionValue& InputActionValue)
{
	if (GetOverlayMode() == AlsOverlayModeTags::Rifle) // Overlay에 총기가 입력되었을때만 재장전가능
	{
		UE_LOG(LogTemp, Warning, TEXT("Reload!!"));
	}else if (GetOverlayMode() != AlsOverlayModeTags::Rifle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Not Hold Weapon!!"));
	}
}

void AShooterCharacter::Input_EquipWeapon(const FInputActionValue& InputActionValue)
{
	SetOverlayMode(AlsOverlayModeTags::Rifle, true);
	UE_LOG(LogTemp, Warning, TEXT("Equip"));
}

void AShooterCharacter::Input_UnequipWeapon(const FInputActionValue& InputActionValue)
{
	SetOverlayMode(AlsOverlayModeTags::Default, true);
	UE_LOG(LogTemp, Warning, TEXT("Unequip"));
}

void AShooterCharacter::Input_StartFire(const FInputActionValue& InputActionValue)
{
	if (GetOverlayMode() == AlsOverlayModeTags::Rifle) // Overlay에 총기가 입력되었을때만 사격가능
	{
		if (InputActionValue.Get<bool>() == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("StartFire"));
			// TODO : 캐릭터 사격로직 추가 [ 화랑님 ]
		}else if (InputActionValue.Get<bool>() == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("StopFire"));
		}
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Not Hold Weapon!!"))
	}
	
}
#pragma endregion

void AShooterCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	ShooterAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AShooterCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	ShooterAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

// 보류함수 [ 화랑님 판단 ]

/*
bool AShooterCharacter::IsInputPressed(const FInputActionValue& InputActionValue)
{
	return InputActionValue.Get<bool>();
}
*/
/*
void AShooterCharacter::SetMaxWalkSpeed(const float NewMaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxWalkSpeed;
}*/