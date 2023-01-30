// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/prototype.h"
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
    virtual int64 _Add(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    virtual int64 _Add(int32 index, const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    virtual int64 _AddWithLimit(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    virtual int64 _Sub(const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    virtual int64 _Sub(int32 index, const FItemData &other) {
        checkNoEntry();
        return 0;
    };

    UFUNCTION(BlueprintCallable)
    virtual void SetLimit(int32 _l) { mLimit = _l; };

    UFUNCTION(BlueprintCallable)
    virtual int32 GetLimit() const { return mLimit; };

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
