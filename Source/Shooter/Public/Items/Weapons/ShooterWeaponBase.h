// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterGamePlayTag.h"
#include "ShooterWeaponBase.generated.h"

class UBoxComponent;
class UShooterGameplayAbility;
class UWeaponAttributeSet;

DECLARE_DELEGATE_OneParam(FonTargetInteractedDelegate, AActor*)

UCLASS()
class SHOOTER_API AShooterWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShooterWeaponBase();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	USceneComponent* GetMuzzleLocation() const { return MuzzleLocation; }

	// 무기 소유자에게 어빌리티 부여
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void GiveAbilityToOwner(AActor* NewOwner);

	FonTargetInteractedDelegate OnWeaponHitTarget;
	FonTargetInteractedDelegate OnWeaponPulledFromTarget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TMap<TSubclassOf<UShooterGameplayAbility>, FGameplayTag> WeaponAbilityMap;

	// 선택 가능한 AttributeSet 클래스 (블루프린트에서 지정)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|GAS")
	TSubclassOf<UWeaponAttributeSet> WeaponAttributeSetClass;

	// 무기 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	// 총알이 발사 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USceneComponent* MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	FORCEINLINE  UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};
