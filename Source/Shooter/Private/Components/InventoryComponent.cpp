#include "Components/InventoryComponent.h"
#include "Components/UI/ShooterUIComponent.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // 슬롯 8개 생성 (빈 슬롯)
    InventorySlots.SetNum(6);
}

TArray<FInventorySlot> UInventoryComponent::GetAllSlots() const
{
    return InventorySlots;
}



void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
    
}

bool UInventoryComponent::AddItem(TSubclassOf<AConsumableItembase> ItemClass, int32 Amount)
{
    if (!ItemClass || Amount <= 0)
    {
        return false;
    }

    AConsumableItembase* DefaultItem = ItemClass->GetDefaultObject<AConsumableItembase>();
    FName RowName = DefaultItem->GetRowName();

    int32 MaxAmountPerSlot = 99; // 기본값
    bool bItemAdded = false;

    if (ItemDataTable)
    {
        static const FString ContextString(TEXT("InventoryComponent::AddItem"));

        FItemDataStruct* Row = ItemDataTable->FindRow<FItemDataStruct>(RowName, ContextString);
        if (Row)
        {
            MaxAmountPerSlot = Row->MaxStackSize;
            UE_LOG(LogTemp, Warning, TEXT("MaxStackSize: %d"), MaxAmountPerSlot);
        }
    }

    int32 RemainingAmount = Amount;

    // 먼저 기존 슬롯에 추가 (MaxStackSize 고려)
    for (FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.ItemClass == ItemClass && Slot.Amount < MaxAmountPerSlot)
        {
            int32 Addable = FMath::Min(MaxAmountPerSlot - Slot.Amount, RemainingAmount);
            Slot.Amount += Addable;
            RemainingAmount -= Addable;

            bItemAdded = true;
            if (RemainingAmount <= 0)
            {
                OnItemAdded.Broadcast(RowName);
                OnInventoryChanged.Broadcast(InventorySlots);
                OnChangeTotalCount.Broadcast(RowName, GetItemCount(RowName));
                return true;
            }
        }
    }

    // 남은 수량을 새 슬롯에 추가
    for (FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.IsEmpty())
        {
            int32 Addable = FMath::Min(MaxAmountPerSlot, RemainingAmount);
            Slot.ItemClass = ItemClass;
            Slot.Amount = Addable;
            Slot.ItemName = Slot.ItemClass->GetDefaultObject<AConsumableItembase>()->GetRowName();

            RemainingAmount -= Addable;
            bItemAdded = true;

            if (RemainingAmount <= 0)
            {
                OnItemAdded.Broadcast(RowName);
                OnInventoryChanged.Broadcast(InventorySlots);
                OnChangeTotalCount.Broadcast(RowName, GetItemCount(RowName));
                return true;
            }
        }
    }

    if (bItemAdded)
    {
        OnItemAdded.Broadcast(RowName);
        OnInventoryChanged.Broadcast(InventorySlots);
        OnChangeTotalCount.Broadcast(RowName, GetItemCount(RowName));
    }
    
    return false;
}


bool UInventoryComponent::RemoveItem(TSubclassOf<AConsumableItembase> ItemClass, int32 Amount)
{
    if (!ItemClass || Amount <= 0)
    {
        return false;
    }

    for (FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.ItemClass == ItemClass)
        {
            if (Slot.Amount >= Amount)
            {
                Slot.Amount -= Amount;
                OnChangeTotalCount.Broadcast(Slot.ItemName, GetItemCount(Slot.ItemName));
                if (Slot.Amount <= 0)
                {
                    Slot.ItemClass = nullptr;
                    Slot.Amount = 0;
                    Slot.ItemName = TEXT("NoneItem");
                }
                OnInventoryChanged.Broadcast(InventorySlots);
                
                return true;
            }
        }
    }

    return false;
}

int32 UInventoryComponent::GetItemCount(FName CountItemName) const
{
    int32 TotalAmount = 0;

    for (const FInventorySlot& Slot : InventorySlots)
    {
        if (Slot.ItemName == CountItemName)
        {
            TotalAmount += Slot.Amount;
        }
    }

    return TotalAmount;
}
