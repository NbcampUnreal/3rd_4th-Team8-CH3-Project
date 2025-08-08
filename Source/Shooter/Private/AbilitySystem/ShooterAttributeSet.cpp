// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ShooterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Components/UI/PawnUIComponent.h"

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
    if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
    {
        float NewPercent = GetCurrentHealth() / GetMaxHealth();
        // Actor 소유자 가져오기
        AActor* OwnerActor = GetOwningActor();
        if (!OwnerActor) return;

        // UI 컴포넌트 가져오기
        UPawnUIComponent* UIComponent = OwnerActor->FindComponentByClass<UPawnUIComponent>();
        if (!UIComponent) return;

        // 체력 변경 알림 보내기
        UIComponent->HandleCurrentHealthChanged(NewPercent);
    }
}
