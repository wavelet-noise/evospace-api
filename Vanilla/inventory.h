// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/item_data.h"
#include "Evospace/Shared/Core/prototype.h"
#include "Evospace/Shared/Vanilla/base_inventory.h"

#include <Containers/Array.h>
#include <Templates/SubclassOf.h>

#include <functional>

#include "Inventory.generated.h"

class UInventoryFilter;

UCLASS(BlueprintType)
/**
 * @brief Inventory. Container like object
 */
class UInventory : public UBaseInventory {
    GENERATED_BODY()

  public:
    UInventory();

    const TArray<FItemData> &GetSlots() const;

    void Resize(int32 size);

    virtual void SortKeyAZ() override;

    void Sort(std::function<bool(const FItemData &l, const FItemData &r)> f);

    void SetAutoSize(bool autosize);

    bool GetAutoSize() const;

    void PopSlot();

    int32 _AddEmpty();

    FItemData &_AddEmpty_GetRef();

    virtual void TrySetFilter(int32 index, UInventoryFilter *filter) override;

  public:
    EVO_LUA_CODEGEN_DB(UInventory, Inventory);
    static void RegisterLua(lua_State *L);
};

UCLASS(BlueprintType)
/**
 * @brief Internal inventory. Container like object
 */
class UInternalInventory : public UInventory {
    GENERATED_BODY()

  public:
    UInternalInventory();

    virtual TSubclassOf<UBaseInventoryWidgetBase>
    GetWidgetClass() const override;

  public:
    EVO_LUA_CODEGEN_DB(UInternalInventory, InternalInventory);
    static void RegisterLua(lua_State *L);
};

UCLASS(BlueprintType)
/**
 * @brief Subscription inventory. Container like object
 */
class USubscriptionInventory : public UInventory {
    GENERATED_BODY()

  public:
    int64 _Add(const FItemData &other) override;

    int64 _Add(int32 index, const FItemData &other) override;

    std::function<void(const FItemData &)> mOnAdd;
};
