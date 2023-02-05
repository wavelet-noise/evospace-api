// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
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
     * @brief Try to add given slot to this inventory
     * @return
     */
    virtual int64 add(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Try to add given slot to specific slot in this inventory
     * @return
     */
    virtual int64 add(int32 index, const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief Try to add given slot to this inventory
     * @return
     */
    virtual int64 add_with_limit(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief
     * @return
     */
    virtual int64 sub(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    /**
     * @brief
     * @return
     */
    virtual int64 sub(int32 index, const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    UFUNCTION(BlueprintCallable)
    /**
     * @brief
     */
    virtual void set_limit(int32 _l) { mLimit = _l; };

    UFUNCTION(BlueprintCallable)
    /**
     * @brief
     * @return
     */
    virtual int32 get_limit() const { return mLimit; };

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    int32 mLimit = INDEX_NONE;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    int32 mHighlight = INDEX_NONE;

    UFUNCTION(BlueprintCallable)
    virtual void SetHighlight(int32 _l) { mHighlight = _l; };

    UFUNCTION(BlueprintCallable)
    virtual int32 GetHighlight() const { return mHighlight; };

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

    virtual void RemoveAllSlots() { checkNoEntry(); }

  protected:
    bool mCanHaveZeroSlot = false;
    bool mZeroLocked = false;

  public:
    EVO_LUA_CODEGEN_DB(UInventoryAccess, InventoryAccess);
    static void RegisterLua(lua_State *L);
};
