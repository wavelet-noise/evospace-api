// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once
#include "Evospace/Shared/Vanilla/base_inventory.h"

#include "SingleSlotInventory.generated.h"

UCLASS()
/**
 * @brief Single slot inventory. Container like object
 */
class USingleSlotInventory : public UBaseInventory {
    GENERATED_BODY()

  public:
    USingleSlotInventory();

    void SetCapacity(int64 value);

    int64 GetCapacity() const;

    void SetSimpleFilter(const UItem *item);

    virtual void TrySetFilter(int32 index, UInventoryFilter *filter) override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

  private:
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int64 mCapacity = 0;
};

UCLASS(BlueprintType)
class UConfiguratibleSingleSlotInventory : public USingleSlotInventory {
    GENERATED_BODY()
};