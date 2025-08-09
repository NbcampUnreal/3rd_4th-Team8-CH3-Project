// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AShooterWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	EED_CurrentEquippedWeapon,
	EED_LeftHand,
	EED_RightHand
};
/**
 * 
 */
UCLASS()
class SHOOTER_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Shooter|Combat")
	void RegisterSpawnedWeapon(
		FGameplayTag InWeaponTagToResister,
		AShooterWeaponBase* InWeaponToResister,
		bool bResisterAsEquippedWeapon = false
	);
	/**
	 * 특정 무기를 검색할 수 있다.
	 * @param InWeaponTagToGet FGameplayTag
	 * @return
	 */
	UFUNCTION(BlueprintCallable, Category = "Shooter|Combat")
	AShooterWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	/**
	 * 장착한 무기를 추적하는데 사용하는 태그
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Shooter|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	/**
	 * 현재 장착된 무기 주소값
	 */
	UFUNCTION(BlueprintCallable, Category = "Shooter|Combat")
	AShooterWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Shooter|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::EED_CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractingActor);

protected:
	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);
	
	UPROPERTY()
	TArray<AActor*> OverlappedActors;

private:
	UPROPERTY()
	TMap<FGameplayTag, AShooterWeaponBase*> CharacterCarriedWeaponMap;
};
