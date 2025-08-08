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

AShooterCharacter::AShooterCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	/*
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true; // 스프링암이 캐릭터 방향 따라감


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // 카메라는 회전 안 하고, 스프링암이 회전함 -> TPS 구조에서 일반적
	*/ 
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
	ETriggerEvent::Started,
	this,
	&ThisClass::Input_Sprint
	);
	/*
	ShooterInputComponent->BindNativeInputAction(
	InputConfigDataAsset,
	ShooterGamePlayTags::InputTag_Sprint,
	ETriggerEvent::Completed,
	this,
	&ThisClass::Input_StopSprint
	);
	*/
	ShooterInputComponent->BindNativeInputAction(
	InputConfigDataAsset,
	ShooterGamePlayTags::InputTag_Weapon_Fire,
	ETriggerEvent::Started,
	this,
	&ThisClass::Input_StartFire
	);
	
	ShooterInputComponent->BindNativeInputAction(
	InputConfigDataAsset,
	ShooterGamePlayTags::InputTag_Weapon_Fire,
	ETriggerEvent::Completed,
	this,
	&ThisClass::Input_StopFire
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
	ShooterGamePlayTags::InputTag_EquipWeapon,
	ETriggerEvent::Started,
	this,
	&ThisClass::Input_EquipWeapon
	);
	
	ShooterInputComponent->BindNativeInputAction(
	InputConfigDataAsset,
	ShooterGamePlayTags::InputTag_UnequipWeapon,
	ETriggerEvent::Started,
	this,
	&ThisClass::Input_UnequipWeapon
	);

	ShooterInputComponent->BindAbilityInputAction(
		InputConfigDataAsset,
		this,
		&ThisClass::Input_AbilityInputPressed,
		&ThisClass::Input_AbilityInputReleased
	);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	//ALS 상태 초기값 설정
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

void AShooterCharacter::Input_Sprint(const FInputActionValue& InputActionValue)
{
	SetDesiredGait(IsInputPressed(InputActionValue) ? AlsGaitTags::Sprinting : AlsGaitTags::Running);
}

void AShooterCharacter::Input_Walk(const FInputActionValue& InputActionValue)
{
	if (GetDesiredGait() == AlsGaitTags::Walking)
		SetDesiredGait(AlsGaitTags::Running);
	else
		SetDesiredGait(AlsGaitTags::Walking);
}

void AShooterCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	// 입력이 true일 때만 점프 실행 (버튼이 눌린 순간)
	if (InputActionValue.Get<bool>())
	{
		Jump();
	}
}

void AShooterCharacter::Input_Crouch(const FInputActionValue& InputActionValue)
{
	if (GetDesiredStance() == AlsStanceTags::Standing)
		SetDesiredStance(AlsStanceTags::Crouching);
	else
		SetDesiredStance(AlsStanceTags::Standing);
}

void AShooterCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Input_Move"));
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	AddMovementInput(YawRotation.RotateVector(FVector::ForwardVector), MovementVector.Y);
	AddMovementInput(YawRotation.RotateVector(FVector::RightVector), MovementVector.X);
}

void AShooterCharacter::Input_Reload(const FInputActionValue& InputActionValue)
{
	
}

void AShooterCharacter::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Input_Look"));
	const FVector2D LookAxis = InputActionValue.Get<FVector2D>();
	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

bool AShooterCharacter::IsInputPressed(const FInputActionValue& InputActionValue)
{
	return InputActionValue.Get<bool>();
}

void AShooterCharacter::SetMaxWalkSpeed(const float NewMaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxWalkSpeed;
}


void AShooterCharacter::Input_EquipWeapon(const FInputActionValue& InputActionValue)
{
}

void AShooterCharacter::Input_UnequipWeapon(const FInputActionValue& InputActionValue)
{
}

void AShooterCharacter::Input_StartFire(const FInputActionValue& InputActionValue)
{
}

void AShooterCharacter::Input_StopFire(const FInputActionValue& InputActionValue)
{
}

void AShooterCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	ShooterAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AShooterCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	ShooterAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

void AShooterCharacter::Input_OnSwitchShoulder()
{
	Camera->SetRightShoulder(!Camera->IsRightShoulder());
}

void AShooterCharacter::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& Unused, float& VerticalLocation)
{
	if (Camera->IsActive())
	{
		Camera->DisplayDebug(Canvas, DisplayInfo, VerticalLocation);
	}

	Super::DisplayDebug(Canvas, DisplayInfo, Unused, VerticalLocation);
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
