// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Containers/Array.h"
#include "Core/item_data.h"
#include "Core/prototype.h"
#include "CoreMinimal.h"

#include "inventory_filter.generated.h"

class UInventoryAccess;
class UItem;

UCLASS(Abstract, BlueprintType)
/**
 * @brief Abstract Class. Inventory filter base class
 */
class UBaseItemFilter : public UPrototype {
    GENERATED_BODY()

  public:
    virtual bool check_slot(const FItemData &data);

  public:
    EVO_LUA_CODEGEN_DB_EX(BaseItemFilter);
    static void lua_reg(lua_State *L);
};

UCLASS(BlueprintType)
/**
 * @brief Inventory white filter
 */
class UItemWhiteFilter : public UBaseItemFilter {
    GENERATED_BODY()

  public:
    virtual bool check_slot(const FItemData &data) override;

    void add_item(const UItem *item);
    void clear();

  protected:
    UPROPERTY()
    TArray<const UItem *> mItems;

  public:
    EVO_LUA_CODEGEN_DB_EX(ItemWhiteFilter);
    static void lua_reg(lua_State *L);
};

UCLASS(BlueprintType)
/**
 * @brief Inventory black filter
 */
class UItemBlackFilter : public UItemWhiteFilter {
    GENERATED_BODY()

  public:
    virtual bool check_slot(const FItemData &data) override;

  public:
    EVO_LUA_CODEGEN_DB_EX(ItemBlackFilter);
    static void lua_reg(lua_State *L);
};

UCLASS(BlueprintType)
/**
 * @brief Inventory filter by another inventory
 */
class UItemInventoryFilter : public UBaseItemFilter {
    GENERATED_BODY()

  public:
    virtual bool check_slot(const FItemData &data) override;

    UPROPERTY()
    UInventoryAccess *inventory = nullptr;

  public:
    EVO_LUA_CODEGEN_DB_EX(ItemInventoryFilter);
    static void lua_reg(lua_State *L);
};
