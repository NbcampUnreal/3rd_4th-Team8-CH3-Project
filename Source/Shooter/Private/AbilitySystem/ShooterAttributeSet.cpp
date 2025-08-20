// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ShooterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ShooterFunctionLibrary.h"
#include "ShooterGamePlayTag.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/ShooterUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

#include "Shooter/ShooterDebugHelper.h"

UShooterAttributeSet::UShooterAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
	InitAttackRange(1.f);
}

void UShooterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(
		CachedPawnUIInterface.IsValid(),
		TEXT("%s IPawnUIInterface를 구현하지 않았습니다. "),
		*Data.Target.GetAvatarActor()->GetActorNameOrLabel()
	);

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(
		PawnUIComponent,
		TEXT("PawnUIComponent를 %s 로 부터 추출 할 수 없습니다."),
		*Data.Target.GetAvatarActor()->GetActorNameOrLabel()
	);

	// 현재체력 상태 변경
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->HandleCurrentHealthChanged(GetCurrentHealth() / GetMaxHealth());

		
		if (GetCurrentHealth() <= 0.f)
		{
			if (UShooterUIComponent* ShooterUIComponent = CachedPawnUIInterface->GetShooterUIComponent())
			{
				ShooterUIComponent->OnShooterDead.Broadcast();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UI 없음"));
			}
		}


		// PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	// 데미지 받았을때 상태 변경
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float PreviousHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(PreviousHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		// 갱신된 체력을 기준으로 비율을 계산
		const float HealthPercentage = GetCurrentHealth() / GetMaxHealth(); 
		AActor* TargetActor = Data.Target.GetAvatarActor();

		if (HealthPercentage <= 0.5f)
		{
		   // 체력이 50% 이하면 "체력 낮음" 태그를 추가
		   UShooterFunctionLibrary::AddGameplayTagToActorIfNone(TargetActor, ShooterGamePlayTags::Shared_Status_LowHealth);
		   UShooterFunctionLibrary::AddGameplayTagToActorIfNone(TargetActor, ShooterGamePlayTags::Boss_Status_Phase2);
		}

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() <= 0.f)
		{
			UShooterFunctionLibrary::AddGameplayTagToActorIfNone(
				TargetActor,
				ShooterGamePlayTags::Shared_Status_Dead
			);		
		}
	}
}
