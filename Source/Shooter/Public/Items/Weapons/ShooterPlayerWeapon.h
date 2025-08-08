// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/ShooterWeaponBase.h"
#include "ShooterTypes/ShooterStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "ShooterPlayerWeapon.generated.h"


UCLASS()
class SHOOTER_API AShooterPlayerWeapon : public AShooterWeaponBase
{
	GENERATED_BODY()

public:
	/**
	 * 이 무기를 통해 부여된 어빌리티 스펙 핸들들을 저장합니다.
	 * 보통 무기 장착 시 AbilitySystemComponent를 통해 부여된 핸들들을 저장하여,
	 * 이후 무기 해제 시 어빌리티 제거에 사용됩니다.
	 *
	 * @param InSpecHandles 부여된 AbilitySpecHandle 리스트
	 */
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	/**
	 * 이 무기가 부여한 어빌리티 스펙 핸들들을 반환합니다.
	 * 주로 무기 해제 시 해당 핸들들을 기반으로 능력을 제거할 때 사용됩니다.
	 *
	 * @return 부여된 AbilitySpecHandle 리스트
	 */
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

	/**
	 * 이 무기의 기본 정보 데이터입니다.
	 * 데미지, 공격 속도, 부여할 어빌리티 목록 등을 포함합니다.
	 * 블루프린트에서 읽을 수 있으나, 외부 C++ 클래스에서는 직접 접근할 수 없습니다.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FShooterPlayerWeaponData ShooterWeaponData;

private:
	/**
	 * 이 무기를 통해 부여된 어빌리티 스펙 핸들 목록입니다.
	 * 무기 해제 시 AbilitySystemComponent로부터 능력을 제거하는 데 사용됩니다.
	 */
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
