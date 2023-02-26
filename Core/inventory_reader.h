// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/item_data.h"
#include "Core/prototype.h"
#include "CoreMinimal.h"

#include <Templates/SubclassOf.h>

#include "inventory_reader.generated.h"

class UBaseInventoryWidget;
class UItem;

UCLASS(Abstract, BlueprintType)
/**
 * @brief Inventory reader. Container like object
 */
class UInventoryReader : public UPrototype {
    GENERATED_BODY()

    // Lua api
public:
    /**
     * @brief Function. Find first slot with same item in inventory
     * @param item Item
     * @return index of slot with item or -1
     */
    virtual int32 find(const UItem *item) const {
        checkNoEntry();
        return INDEX_NONE;
    };

    /**
     * @brief Function. 
     * @return 
     */
    virtual bool is_empty() const {
        checkNoEntry();
        return true;
    };

    /**
     * @brief Function. Calculate sum of counts of all items with same UItem in this inventory
     * @param item UItem
     * @return item count
     */
    virtual int64 sum(const UItem *item) const {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Function. 
     * @param index 
     * @return 
     */
    virtual const FItemData &get(int32 index) const {
        checkNoEntry();
        const static FItemData dummy;
        return dummy;
    };

    /**
     * @brief Function. 
     * @param index 
     * @return 
     */
    virtual const FItemData &safe_get(int32 index) const {
        checkNoEntry();
        const static FItemData dummy;
        return dummy;
    };

    virtual int64 GetSlotCapacity(int32 index) const {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Function. get this inventory slot count
     * @return slot count
     */
    virtual int32 size() const {
        checkNoEntry();
        return 0;
    };

    UFUNCTION(BlueprintCallable)
    virtual TSubclassOf<UBaseInventoryWidgetBase> GetWidgetClass() const {
        checkNoEntry();
        return nullptr;
    };

    UFUNCTION(BlueprintCallable)
    int32 Num() const { return size(); }

    /*UFUNCTION(BlueprintCallable)
            bool IsEmpty() const { return IsEmpty(); }*/
  public:
    EVO_LUA_CODEGEN_DB(UInventoryReader, InventoryReader);
    static void RegisterLua(lua_State *L);
};
