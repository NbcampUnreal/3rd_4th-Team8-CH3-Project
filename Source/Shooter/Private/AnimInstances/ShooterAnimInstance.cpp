// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ShooterAnimInstance.h"
#include "Characters/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UShooterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		/* 캐릭터의 무브먼트 컴포넌트 가져오기 */
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UShooterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningMovementComponent || !OwningCharacter)
	{
		return;
	}
	/* 무브먼트 컴포넌트의 속도를 가져옴 */
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().Size2D() > 0.0f;

	// 점프 상태 (공중에 있는지 여부)
	IsJump = OwningMovementComponent->IsFalling();

	// 캐릭터의 앵글 계산
	// 캐릭터가 움직이고 있을 때만 앵글을 계산하여 정지 시 불필요한 흔들림을 방지합니다.
	if (GroundSpeed > KINDA_SMALL_NUMBER)
	{
		const FVector Velocity = OwningCharacter->GetVelocity();
		const FRotator MovementRot = Velocity.ToOrientationRotator(); // 이동 방향
		const FRotator ActorRot = OwningCharacter->GetActorRotation(); // 캐릭터가 보고 있는 방향

		// Yaw 차이를 계산
		float YawDiff = FMath::FindDeltaAngleDegrees(ActorRot.Yaw, MovementRot.Yaw);

		Angle = YawDiff;
	}
	else
	{
		Angle = 0.f;
	}
};