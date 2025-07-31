// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterGamePlayTag.h"
#include "ShooterWeaponBase.generated.h"

class UShooterGameplayAbility;

UCLASS()
class SHOOTER_API AShooterWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShooterWeaponBase();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	USceneComponent* GetMuzzleLocation() const { return MuzzleLocation; }

	// 발사 어빌리티 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UShooterGameplayAbility> FireAbilityClass;

	// 리로드 어빌리티 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UShooterGameplayAbility> ReloadAbilityClass;

	// 장착 어빌리티 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UShooterGameplayAbility> WeaponEquipAbilityClass;

	// 무기 소유자에게 어빌리티 부여
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void GiveAbilityToOwner(AActor* NewOwner);

protected:
	// 선택 가능한 AttributeSet 클래스 (블루프린트에서 지정)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|GAS")
	TSubclassOf<UAttributeSet> WeaponAttributeSetClass;

	// 무기 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	// 총알이 발사 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USceneComponent* MuzzleLocation;
};
