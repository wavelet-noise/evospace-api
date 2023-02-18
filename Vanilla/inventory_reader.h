// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
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

    // Add interface functions to this class. This is the class that will be
    // inherited to implement this interface.
  public:
    virtual int32 min() const {
        checkNoEntry();
        return 0;
    };

    virtual int32 max() const {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Find first slot with same item in inventory 
     * @param item Item
     * @return index of slot with item or -1
     */
    virtual int32 find(const UItem *item) const {
        checkNoEntry();
        return INDEX_NONE;
    };

    virtual bool IsEmpty() const {
        checkNoEntry();
        return true;
    };

    virtual int64 sum(const UItem *item) const {
        checkNoEntry();
        return 0;
    };

    virtual const FItemData &get(int32 index) const {
        checkNoEntry();
        const static FItemData dummy;
        return dummy;
    };

    virtual const FItemData &safe_get(int32 index) const {
        checkNoEntry();
        const static FItemData dummy;
        return dummy;
    };

    virtual int64 GetSlotCapacity(int32 index) const {
        checkNoEntry();
        return 0;
    };

    virtual int32 _Num() const {
        checkNoEntry();
        return 0;
    };

    UFUNCTION(BlueprintCallable)
    virtual TSubclassOf<UBaseInventoryWidgetBase> GetWidgetClass() const {
        checkNoEntry();
        return nullptr;
    };

    UFUNCTION(BlueprintCallable)
    int32 Num() const { return _Num(); }

    /*UFUNCTION(BlueprintCallable)
            bool IsEmpty() const { return IsEmpty(); }*/
  public:
    EVO_LUA_CODEGEN_DB(UInventoryReader, InventoryReader);
    static void RegisterLua(lua_State *L);
};
