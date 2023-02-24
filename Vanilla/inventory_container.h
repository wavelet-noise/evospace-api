// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/inventory_access.h"
#include "Core/item_data.h"
#include "Core/prototype.h"
#include "CoreMinimal.h"

#include "inventory_container.generated.h"

UCLASS()
/**
 * @brief Inventory container. Container like object
 */
class UInventoryContainer : public UInventoryAccess {
    GENERATED_BODY()
  public:
    virtual TSubclassOf<UBaseInventoryWidgetBase>
    GetWidgetClass() const override;

    virtual int32 min() const override;

    virtual int32 find(const UItem *item) const override;

    virtual bool IsEmpty() const override;

    virtual int64 sum(const UItem *item) const override;

    virtual const FItemData &get(int32 index) const override;

    virtual const FItemData &safe_get(int32 index) const override;

    virtual int64 GetSlotCapacity(int32 index) const override;

    // TODO: rename num
    virtual int32 size() const override;

    virtual void SortKeyAZ() override;

    virtual int64 add(const FItemData &other) override;

    virtual int64 add_to(const FItemData &other, int32 index) override;

    virtual int64 sub(const FItemData &other) override;

    virtual int64 sub_from(const FItemData &from, int32 index) override;

    virtual void TrySetFilter(int32 index, UInventoryFilter *filter) override;

    virtual int64 add_with_limit(const FItemData &other) override;

    // 	void BindInventory(UInventoryContainer *container);
    //
    // 	void BindInventory(UBaseInventory *inventory);

    void BindInventory(UInventoryAccess *inventory);

    UInventoryAccess *GetAccess(int32 i) const;

    void UnbindAll();

    virtual void SetCanHaveZeroSlot(bool value) override;

    UFUNCTION(
        BlueprintCallable, meta = (AllowPrivateAccess = "true"), BlueprintPure
    )
    TArray<UInventoryAccess *> &GetList();

    virtual void Sanitize() override;

  private:
    UPROPERTY()
    TArray<UInventoryAccess *> mList;

    int32 ListIndex(int32 &index) const;

  public:
    int32 InventoryCount();

  public:
    EVO_LUA_CODEGEN_DB(UInventoryContainer, InventoryContainer);
    static void RegisterLua(lua_State *L);
};
