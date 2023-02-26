// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/prototype.h"
#include "CoreMinimal.h"
#include "inventory_reader.h"

#include "inventory_access.generated.h"

class UInventoryFilter;

UCLASS(Abstract, BlueprintType)
/**
 * @brief Inventory access. Container like object
 */
class UInventoryAccess : public UInventoryReader {
    GENERATED_BODY()

  public:
    /**
     * @brief Function. Try to add given slot to this inventory
     * @return remainder after addition. 0 if all count in slot is transferred
     */
    virtual int64 add(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Function. Try to add given slot to specific slot in this inventory
     * @return remainder after addition. 0 if all count in slot is transferred
     */
    virtual int64 add_to(const FItemData &other, int32 index) {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Function. Try to add given slot to this inventory but using only [0, limit) slots
     * @return remainder after addition. 0 if all count in slot is transferred
     */
    virtual int64 add_with_limit(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Function. 
     * @return remainder after subtraction. 0 if all count in slot is transferred
     */
    virtual int64 sub(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Function. 
     * @return
     */
    virtual int64 sub_from(const FItemData &other, int32 index) {
        checkNoEntry();
        return 0;
    };

    UPROPERTY(BlueprintReadWrite, EditAnywhere);
    /**
     * @brief Property. Slot count that can be accessed with add_with_limit() function or -1 for no limit
     */
    int32 limit = INDEX_NONE;

    /**
     * @brief Function. remove all slots from inventory
     */
    virtual void reset() { checkNoEntry(); }

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    /**
     * @brief Property. currently hovered slot or -1 for nothing
     */
    int32 hovered = INDEX_NONE;

    virtual void SetCanHaveZeroSlot(bool value) {
        if (!mZeroLocked)
            mCanHaveZeroSlot = value;
    }
    virtual void Sanitize() {}

    virtual void TrySetFilter(int32 index, UInventoryFilter *filter) {
        checkNoEntry();
    }

    UFUNCTION(BlueprintCallable)
    virtual void SortKeyAZ() {}

  protected:
    bool mCanHaveZeroSlot = false;
    bool mZeroLocked = false;

  public:
    EVO_LUA_CODEGEN_DB(UInventoryAccess, InventoryAccess);
    static void RegisterLua(lua_State *L);
};
