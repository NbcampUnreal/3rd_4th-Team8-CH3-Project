// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/ShooterUIComponent.h"

void UShooterUIComponent::HandleCurrentAmmoChanged(float NewAmmo)
{
    UE_LOG(LogTemp, Log, TEXT("[ShooterUIComponent] 총알 변경 감지: %.2f"), NewAmmo);

    // HUD 위젯에 알리기 위해 브로드캐스트
    OnCurrentAmmoChanged.Broadcast(NewAmmo);
}
