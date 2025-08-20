#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ALSStateComponent.generated.h"

class AAlsCharacter; // 전방 선언(헤더 의존 최소화)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API UALSStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UALSStateComponent();

	// ---- 공통 API (BP/C++) ----
	UFUNCTION(BlueprintCallable, Category="ALS")
	void SetDesiredGaitTag(FGameplayTag NewGait);

	UFUNCTION(BlueprintCallable, Category="ALS")
	FGameplayTag GetCurrentGaitTag() const;

	UFUNCTION(BlueprintCallable, Category="ALS")
	void SetDesiredStanceTag(FGameplayTag NewStance);

	UFUNCTION(BlueprintCallable, Category="ALS")
	FGameplayTag GetCurrentStanceTag() const;

	UFUNCTION(BlueprintCallable, Category="ALS")
	void SetDesiredRotationModeTag(FGameplayTag NewRotationMode);

	UFUNCTION(BlueprintCallable, Category="ALS")
	FGameplayTag GetCurrentRotationModeTag() const;

	// 소유자가 ALS 캐릭터인지(자동 판별)
	UFUNCTION(BlueprintPure, Category="ALS")
	bool IsAlsCharacter() const { return bIsALS; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="ALS")
	bool bIsALS = false;

	// ALS 미사용 캐릭터용 로컬 상태 저장
	UPROPERTY(EditAnywhere, Category="ALS")
	FGameplayTag LocalGait;

	UPROPERTY(EditAnywhere, Category="ALS")
	FGameplayTag LocalStance;

	UPROPERTY(EditAnywhere, Category="ALS")
	FGameplayTag LocalRotationMode;
};
