// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ShooterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "ShooterFunctionLibrary.h"
#include "ShooterGamePlayTag.h"
#include "Components/UI/PawnUIComponent.h"
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
	// TODO: ui 변경에 대한 로직 작성 필요
	// if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	// {
	// 	float NewPercent = GetCurrentHealth() / GetMaxHealth();
	// 	// Actor 소유자 가져오기
	// 	AActor* OwnerActor = GetOwningActor();
	// 	if (!OwnerActor) return;
	//
	// 	// UI 컴포넌트 가져오기
	// 	UPawnUIComponent* UIComponent = OwnerActor->FindComponentByClass<UPawnUIComponent>();
	// 	if (!UIComponent) return;
	//
	// 	// 체력 변경 알림 보내기
	// 	UIComponent->HandleCurrentHealthChanged(NewPercent);
	// }


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
		// PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	// 데미지 받았을때 상태 변경
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float PreviousHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(PreviousHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("이전체력: %f, 데미지 완료: %f"),
			PreviousHealth,
			DamageDone
		);

		Debug::Print(DebugString, FColor::Green);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() <= 0.f)
		{
			UShooterFunctionLibrary::AddGameplayTagToActorIfNone(
				Data.Target.GetAvatarActor(),
				ShooterGamePlayTags::Shared_Status_Dead
			);
		}
	}
}
