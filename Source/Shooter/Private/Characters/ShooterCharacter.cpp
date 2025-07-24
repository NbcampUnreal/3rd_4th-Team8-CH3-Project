// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ShooterGamePlayTag.h"
#include "Components/Input/ShooterInputComponent.h"
#include "Components/Combat/ShooterCombatComponent.h"

AShooterCharacter::AShooterCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true; // 스프링암이 캐릭터 방향 따라감


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // 카메라는 회전 안 하고, 스프링암이 회전함 -> TPS 구조에서 일반적

	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동방향을 바라보게
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	ShooterCombatComponent = CreateDefaultSubobject<UShooterCombatComponent>(TEXT("ShooterCombatComponent"));
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

	UShooterInputComponent* ShooterInputComponent = CastChecked<UShooterInputComponent>(PlayerInputComponent);
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
		&ThisClass::Input_Look
	);

	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Look_Gamepad,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Look
	);
	ShooterInputComponent->BindNativeInputAction(
		InputConfigDataAsset,
		ShooterGamePlayTags::InputTag_Jump,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Jump
	);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AShooterCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation = FRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
	// 사용자 입력이 앞/뒤(Y축)일 경우
	if (MovementVector.Y != 0.f)
	{
		// 카메라 기준의 '앞 방향'을 계산하고
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		// 그 방향으로 입력 세기를 적용해 이동시킴
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AShooterCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AShooterCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	// 입력이 true일 때만 점프 실행 (버튼이 눌린 순간)
	if (InputActionValue.Get<bool>())
	{
		Jump();
	}
}
