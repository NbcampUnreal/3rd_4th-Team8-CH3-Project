#include "Components/ALSStateComponent.h"
#include "GameFramework/Actor.h"

// ALS 플러그인 헤더 (Refactored ALS 기준)
#include "AlsCharacter.h" // SetDesiredGait(FGameplayTag), GetGait() 등 사용

UALSStateComponent::UALSStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UALSStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// 소유자가 ALS 캐릭터인지 1회만 판별
	if (GetOwner() && Cast<AAlsCharacter>(GetOwner()))
	{
		bIsALS = true;
	}
}

void UALSStateComponent::SetDesiredGaitTag(FGameplayTag NewGait)
{
	if (bIsALS)
	{
		if (auto* Als = Cast<AAlsCharacter>(GetOwner()))
		{
			Als->SetDesiredGait(NewGait);
			return;
		}
	}
	// ALS 미사용: 로컬 상태만 기록
	LocalGait = NewGait;
}

FGameplayTag UALSStateComponent::GetCurrentGaitTag() const
{
	if (bIsALS)
	{
		if (auto* Als = Cast<AAlsCharacter>(GetOwner()))
		{
			return Als->GetGait();
		}
	}
	return LocalGait;
}

void UALSStateComponent::SetDesiredStanceTag(FGameplayTag NewStance)
{
	if (bIsALS)
	{
		if (auto* Als = Cast<AAlsCharacter>(GetOwner()))
		{
			Als->SetDesiredStance(NewStance);
			return;
		}
	}
	LocalStance = NewStance;
}

FGameplayTag UALSStateComponent::GetCurrentStanceTag() const
{
	if (bIsALS)
	{
		if (auto* Als = Cast<AAlsCharacter>(GetOwner()))
		{
			return Als->GetStance();
		}
	}
	return LocalStance;
}

void UALSStateComponent::SetDesiredRotationModeTag(FGameplayTag NewRotationMode)
{
	if (bIsALS)
	{
		if (auto* Als = Cast<AAlsCharacter>(GetOwner()))
		{
			Als->SetDesiredRotationMode(NewRotationMode);
			return;
		}
	}
	LocalRotationMode = NewRotationMode;
}

FGameplayTag UALSStateComponent::GetCurrentRotationModeTag() const
{
	if (bIsALS)
	{
		if (auto* Als = Cast<AAlsCharacter>(GetOwner()))
		{
			return Als->GetRotationMode();
		}
	}
	return LocalRotationMode;
}
