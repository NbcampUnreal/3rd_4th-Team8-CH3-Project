// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.generated.h"

class AConsumableItembase;

USTRUCT(BlueprintType)
struct SHOOTER_API FItemDataStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    // 기본 생성자에서 기본값 초기화
    FItemDataStruct()
        : ItemName(FText::FromString(TEXT("Default Item")))
        , ItemDescription(FText::FromString(TEXT("Default Description")))
        , ItemClass(nullptr)
        , ItemIcon(nullptr)
        , MaxStackSize(1)
    {
    }

    // 아이템 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemName;

    // 아이템 설명
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemDescription;

    // 아이템 클래스 (아이템 액터 클래스)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    TSubclassOf<class AConsumableItembase> ItemClass;

    // 아이템 아이콘 (텍스처)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* ItemIcon;

    // 최대 스택 수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxStackSize;
};
