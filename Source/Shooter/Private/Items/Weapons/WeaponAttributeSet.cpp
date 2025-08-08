// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WeaponAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Components/UI/ShooterUIComponent.h"
#include "Shooter/ShooterDebugHelper.h"

UWeaponAttributeSet::UWeaponAttributeSet()
{
	InitMaxAmmo(30.f);
	InitCurrentAmmo(GetMaxAmmo());
}

void UWeaponAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Debug::Print("test");
	if (Data.EvaluatedData.Attribute == GetCurrentAmmoAttribute())
	{
		float NewAmmo = GetCurrentAmmo();

		// Actor 소유자 가져오기
		AActor* OwnerActor = GetOwningActor();
		if (!OwnerActor)
		{
			return;
		}

		// UI 컴포넌트 가져오기
		UShooterUIComponent* UIComponent = OwnerActor->FindComponentByClass<UShooterUIComponent>();
		if (!UIComponent)
		{
			return;
		}

		// 총알 변경 알림 보내기
		UIComponent->HandleCurrentAmmoChanged(NewAmmo);
	}
}
