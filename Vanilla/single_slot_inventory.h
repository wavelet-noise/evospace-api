// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once
#include "Core/base_inventory.h"

#include "single_slot_inventory.generated.h"

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

public:
    EVO_LUA_CODEGEN_DB_EX(SingleSlotInventory);
    static void RegisterLua(lua_State *L);
};

UCLASS(BlueprintType)
class UConfiguratibleSingleSlotInventory : public USingleSlotInventory {
    GENERATED_BODY()
};