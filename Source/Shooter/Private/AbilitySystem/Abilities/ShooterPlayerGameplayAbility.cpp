// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ShooterPlayerGameplayAbility.h"

#include "ShooterGamePlayTag.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "Characters/ShooterCharacter.h"
#include "Controllers/ShooterController.h"
#include "Shooter/ShooterDebugHelper.h"

/**
 * @brief ActorInfo에서 AShooterCharacter를 가져오고, 이를 캐시에 저장하여 반환하는 함수입니다.
 *
 * 1. 캐시된 캐릭터가 유효하지 않을 경우(최초 접근 또는 이미 파괴된 경우) ActorInfo에서 AvatarActor를 가져와 AShooterCharacter로 캐스팅하고 캐시에 저장합니다.
 * 2. 캐시된 캐릭터가 유효하면 이를 반환하고, 무효하거나 존재하지 않으면 nullptr을 반환합니다.
 *
 * @return 캐시된 AShooterCharacter 포인터. 유효하지 않은 경우 nullptr을 반환합니다.
 */
AShooterCharacter* UShooterPlayerGameplayAbility::GetShooterCharacterFromActorInfo()
{
	if (!CachedShooterCharacter.IsValid())
	{
		CachedShooterCharacter = Cast<AShooterCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedShooterCharacter.IsValid() ? CachedShooterCharacter.Get() : nullptr;
}

/**
 * @brief ActorInfo에서 AShooterController를 가져오고, 이를 캐시에 저장하여 반환하는 함수입니다.
 *
 *	1. 캐시된 컨트롤러가 유효하지 않을 경우(최초 접근 또는 이미 파괴된 경우) ActorInfo에서 PlayerController를 가져와 AShooterController로 캐스팅하고 캐시에 저장합니다.
 *	2. 캐시된 컨트롤러가 유효하면 이를 반환하고, 무효하거나 존재하지 않으면 nullptr을 반환합니다.
 *
 * @return 캐시된 AShooterController 포인터. 유효하지 않은 경우 nullptr을 반환합니다.
 */
AShooterController* UShooterPlayerGameplayAbility::GetShooterControllerFromActorInfo()
{
	if (!CachedShooterController.IsValid())
	{
		CachedShooterController = Cast<AShooterController>(CurrentActorInfo->PlayerController);
	}
	return CachedShooterController.IsValid() ? CachedShooterController.Get() : nullptr;
}

UShooterCombatComponent* UShooterPlayerGameplayAbility::GetShooterCombatComponentFromActorInfo()
{
	const AShooterCharacter* ShooterCharacter = GetShooterCharacterFromActorInfo();
	return ShooterCharacter ? ShooterCharacter->GetShooterCombatComponent() : nullptr;
}

/**
 * - 지정된 GameplayEffect 클래스와 입력 정보를 바탕으로 FGameplayEffectSpecHandle을 생성
 * - 이 함수는 무기의 기본 데미지와 현재 공격 상태(공격 태그, 콤보 수 등)를 SetByCaller 값으로 전달
 * - 생성된 SpecHandle은 대상에게 이펙트를 적용할 때 사용
 *
 * @param EffectClass 적용할 GameplayEffect 클래스 (예: 데미지 이펙트)
 * @param InWeaponBaseDamage 무기의 기본 데미지 수치 (SetByCaller로 전달)
 * @param InCurrentAttackTypeTag 현재 공격 타입을 나타내는 태그 (예: 공격1, 차지공격 등)
 * @param InUsedComboCount 현재 콤보 수치 (SetByCaller로 전달)
 * @return 구성된 FGameplayEffectSpecHandle 인스턴스
 */
FGameplayEffectSpecHandle UShooterPlayerGameplayAbility::MakeShooterDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass,
	float InWeaponBaseDamage,
	FGameplayTag InCurrentAttackTypeTag
)
{
	check(EffectClass);

	// 이펙트에 사용될 컨텍스트 핸들 생성 (누가 시전했는지, 어떤 스킬인지 등 정보를 담음)
	FGameplayEffectContextHandle ContextHandle = GetShooterAbilitySystemComponentFromActorInfo()->MakeEffectContext();

	// Ability 정보 추가 (누가 발동했는지)
	ContextHandle.SetAbility(this);

	// SourceObject 설정: 일반적으로 무기, 액터 등 이펙트의 "출처" 객체
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());

	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	// !!실제 GameplayEffect 사양을 생성함 실제 적용은 안되는단계 (어떤 효과를 어떤 레벨로 누구에게 적용할지)
	FGameplayEffectSpecHandle EffectSpecHandle = GetShooterAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass, // 사용할 이펙트 클래스
		GetAbilityLevel(), // 현재 어빌리티 레벨
		ContextHandle // 위에서 만든 컨텍스트 정보
	);

	// SetByCaller 방식으로 데미지 값 설정 (이펙트 블루프린트에서 동적으로 받을 수 있음)
	// TMap<FGameplayTag, float> SetByCallerTagMagnitudes; -> key: ShooterGamePlayTags::Shared_SetByCaller_BaseDamage, value: InWeaponBaseDamage
	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		ShooterGamePlayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);

	// 완성된 이펙트 스펙 핸들을 반환 -> 이걸로 ApplyGameplayEffectToTarget() 같은 함수에 넘겨서 실제 적용함
	return EffectSpecHandle;
}
