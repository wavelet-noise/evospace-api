// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.

#pragma once
#include "Core/base_inventory.h"

#include "single_slot_inventory.generated.h"

UCLASS()
/**
 * @brief Single slot inventory. Container like object
 */
class USingleSlotInventory : public UBaseInventory {
    GENERATED_BODY()

    // Lua api
  public:
    UPROPERTY(BlueprintReadOnly)
    int64 capacity = 0;

  public:
    USingleSlotInventory();

    void SetSimpleFilter(const UItem *item);

    virtual void TrySetFilter(int32 index, UBaseItemFilter *filter) override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

  private:
  public:
    EVO_LUA_CODEGEN_DB_EX(SingleSlotInventory);
    static void lua_reg(lua_State *L);
};

UCLASS(BlueprintType)
class UConfiguratibleSingleSlotInventory : public USingleSlotInventory {
    GENERATED_BODY()
};