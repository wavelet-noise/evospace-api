// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/item_data.h"
#include "Evospace/Shared/Core/prototype.h"
#include "Evospace/Shared/Vanilla/inventory_access.h"

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

    virtual int32 _Min() const override;

    virtual int32 _Max() const override;

    virtual int32 _Find(const UItem *item) const override;

    virtual int32 _FindEmpty() const override;

    virtual int32 _FindNotEmpty() const override;

    virtual bool IsEmpty() const override;

    virtual int64 _Sum(const UItem *item) const override;

    virtual const FItemData &_Get(int32 index) const override;

    virtual const FItemData &_SafeGet(int32 index) const override;

    virtual int64 GetSlotCapacity(int32 index) const override;

    virtual int32 _Num() const override;

    virtual void SortKeyAZ() override;

    virtual int64 _Add(const FItemData &other) override;

    virtual int64 _Add(int32 index, const FItemData &other) override;

    virtual int64 _Sub(const FItemData &other) override;

    virtual int64 _Sub(int32 index, const FItemData &from) override;

    virtual void TrySetFilter(int32 index, UInventoryFilter *filter) override;

    virtual int64 _AddWithLimit(const FItemData &other) override;

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
