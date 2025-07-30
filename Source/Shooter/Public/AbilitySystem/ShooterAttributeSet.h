// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ShooterAbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ShooterAttributeSet.generated.h"

class IPawnUIInterface;

/**
 * �־��� Ŭ����(ClassName)�� ��Ʈ����Ʈ(PropertyName)�� ����
 * �ʿ��� Getter, Setter, Initializer ��ƿ��Ƽ �Լ��� �ڵ����� �����մϴ�.
 *
 * - FGameplayAttribute�� �������� ���� �Լ�
 * - ��Ʈ����Ʈ �� ��ȸ �Լ�
 * - ��Ʈ����Ʈ �� ���� �Լ�
 * - ��Ʈ����Ʈ �ʱ�ȭ �Լ�
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UShooterAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UShooterAttributeSet, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UShooterAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UShooterAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UShooterAttributeSet, DefensePower);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UShooterAttributeSet, DamageTaken);
};
