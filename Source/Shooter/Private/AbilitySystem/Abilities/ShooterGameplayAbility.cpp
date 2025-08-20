// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ShooterGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"


/**
 * 이 어빌리티가 액터(예: 캐릭터)에게 부여될 때 호출됨
 * @param ActorInfo    어빌리티가 부여된 액터에 대한 정보
 * @param Spec         어빌리티의 사양(레벨, 입력 바인딩 등)을 담고 있는 구조체
 */
void UShooterGameplayAbility::OnGiveAbility(
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec
)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EShooterAbilityActivationPolicy::EWA_OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

/**
 * 능력이 종료될 때 호출되는 함수.
 * 
 * 이 함수는 능력의 정상 종료 또는 취소 시 호출되며, 부모 클래스의 EndAbility를 호출한 뒤
 * 특정 활성화 정책(EShooterAbilityActivationPolicy::EWA_OnGiven)에 따라 능력을 시스템에서 제거할 수 있음.
 * 
 * @param Handle                종료되는 능력의 핸들.
 * @param ActorInfo             능력을 소유한 액터에 대한 정보.
 * @param ActivationInfo        능력의 활성화 상태 정보.
 * @param bReplicateEndAbility  이 종료 동작을 네트워크에 복제할지에 대한 여부.
 * @param bWasCancelled         능력이 취소되어 종료되었는지 여부.
 */
void UShooterGameplayAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled
)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EShooterAbilityActivationPolicy::EWA_OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UShooterGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

/**
 * 지정된 대상 액터에게 준비된 GameplayEffectSpec을 적용
 *
 * 이 함수는 대상 액터의 AbilitySystemComponent(ASC)를 가져오고,
 * 전달된 GameplayEffectSpecHandle이 유효한지 확인한 뒤,
 * 현재 능력의 ASC를 통해 대상에게 효과를 적용
 *
 * @param TargetActor         효과를 적용할 대상 액터
 * @param InSpecHandle        적용할 준비된 GameplayEffectSpec을 담고 있는 핸들
 * @return                    적용된 액티브 효과의 핸들
 */
FActiveGameplayEffectHandle UShooterGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	// !!타겟에게 적용
	return GetShooterAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data, // 핸들에서 실제 효과 사양(Spec)을 가져옴
		TargetASC // 대상의 ASC
	);
}

/**
 * 현재 능력을 실행 중인 액터의 AbilitySystemComponent를 가져와서
 * UShooterAbilitySystemComponent 타입으로 캐스팅하여 반환
 *
 * 이 함수는 Shooter 전용 AbilitySystemComponent가 필요할 때 사용
 * (예: 공통 ASC가 아닌 Shooter에 특화된 기능을 사용할 경우)
 *
 * @return Shooter 전용 AbilitySystemComponent (UShooterAbilitySystemComponent*) 포인터
 */
UShooterAbilitySystemComponent* UShooterGameplayAbility::GetShooterAbilitySystemComponentFromActorInfo() const
{
	return Cast<UShooterAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

/**
 * 지정된 타겟 액터에게 GameplayEffectSpecHandle을 적용하고, 그 결과에 따라 성공 여부를 반환
 * 
 * 이 함수는 블루프린트에서 호출 가능한 래퍼 함수이며, 내부적으로 NativeApplyEffectSpecHandleToTarget을 호출하여
 * 실제 효과를 적용
 * 
 * 적용 결과는 OutSuccessType에 저장되며, 적용 성공 여부를 ESC_Successful 또는 ESC_Failed로 나타냅
 *
 * @param TargetActor       효과를 적용할 대상 액터.
 * @param InSpecHandle      적용할 GameplayEffect의 사양 핸들.
 * @param OutSuccessType    효과 적용의 성공 여부가 저장. (성공 시 ESC_Successful, 실패 시 ESC_Failed)
 * 
 * @return FActiveGameplayEffectHandle  적용된 효과의 핸들을 반환. (실패 시 Invalid 핸들일 수 있음)
 */
FActiveGameplayEffectHandle UShooterGameplayAbility::BP_ApplyEffectSpecHandleToTarget(
	AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle,
	EShooterSuccessType& OutSuccessType
)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType =
		ActiveGameplayEffectHandle.WasSuccessfullyApplied()
			? EShooterSuccessType::ESC_Successful
			: EShooterSuccessType::ESC_Failed;

	return ActiveGameplayEffectHandle;
}
