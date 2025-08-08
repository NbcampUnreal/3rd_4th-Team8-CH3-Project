#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ConsumableItems/ConsumableItembase.h"
#include "Items/Structs/ItemDataStruct.h"
#include "InventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AConsumableItembase> ItemClass = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Amount = 0;

    bool IsEmpty() const { return ItemClass == nullptr || Amount <= 0; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemName = TEXT("NoneItem");
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryChanged, const TArray<FInventorySlot>&, ChangedSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemPickupDelegate, TSubclassOf<AConsumableItembase>, ItemClass);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTER_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();

    /** 아이템 추가 */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(TSubclassOf<AConsumableItembase> ItemClass, int32 Amount);

    /** 아이템 제거 */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(TSubclassOf<AConsumableItembase> ItemClass, int32 Amount);

    /** 아이템 개수 조회 */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetItemCount(TSubclassOf<AConsumableItembase> ItemClass) const;

    /** 아이템 데이터 테이블 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    UDataTable* ItemDataTable;

    UPROPERTY(BlueprintAssignable)
    FOnInventoryChanged OnInventoryChanged;

    UPROPERTY(BlueprintAssignable)
    FOnItemPickupDelegate OnItemAdded;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    TArray<FInventorySlot> GetAllSlots() const;

protected:
    virtual void BeginPlay() override;

    /** 슬롯 배열 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FInventorySlot> InventorySlots;
};