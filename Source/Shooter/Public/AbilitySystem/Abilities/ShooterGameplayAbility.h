// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ShooterGameplayAbility.generated.h"


UENUM(BlueprintType)
enum class EShooterAbilityActivationPolicy : uint8
{
	/* 입력 또는 게임플레이 이벤트를통해 트리거 될때 */
	EWA_OnTriggered,

	/* 대상에게 주어지면 바로 능력 발동 */
	EWA_OnGiven
};

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	// ~ Begin UGameplayAbility Interface.
	/**
	 * 이 어빌리티가 액터(예: 캐릭터)에게 부여될 때 호출됩니다.
	 * @param ActorInfo    어빌리티가 부여된 액터에 대한 정보입니다.
	 * @param Spec         어빌리티의 사양(레벨, 입력 바인딩 등)을 담고 있는 구조체입니다.
	 */
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	/**
	 * 어빌리티가 종료될 때 호출됩니다. 종료 원인은 정상적인 종료 또는 취소일 수 있습니다.
	 * @param Handle               어빌리티를 식별하기 위한 핸들입니다.
	 * @param ActorInfo            어빌리티를 가진 액터에 대한 정보입니다.
	 * @param ActivationInfo       어빌리티가 어떻게 활성화되었는지에 대한 정보입니다.
	 * @param bReplicateEndAbility true이면, 어빌리티 종료 정보를 네트워크를 통해 클라이언트에도 전파합니다.
	 * @param bWasCancelled        true이면, 어빌리티가 중간에 취소되어 종료된 것입니다.
	 */
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
		bool bWasCancelled
	) override;
	// ~ End UGameplayAbility Interface.

protected:
	UPROPERTY(EditAnywhere, Category = "WarriorAbility")
	EShooterAbilityActivationPolicy AbilityActivationPolicy = EShooterAbilityActivationPolicy::EWA_OnTriggered;
};
