// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/PawnUIComponent.h"

void UPawnUIComponent::HandleCurrentHealthChanged(float NewPercent)
{
    UE_LOG(LogTemp, Log, TEXT("[PawnUIComponent] 체력 변경 감지: %.2f"), NewPercent);

    // HUD 위젯에 알리기 위해 브로드캐스트
    OnCurrentHealthChanged.Broadcast(NewPercent);
}
