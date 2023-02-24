// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/inventory_access.h"
#include "Core/item_data.h"
#include "Core/prototype.h"
#include "CoreMinimal.h"

#include <Templates/Function.h>
#include <Templates/SubclassOf.h>

#include "base_inventory.generated.h"

class UInventoryFilter;
class UBaseInventory;
class UItem;

UCLASS(Abstract, BlueprintType)
/**
 * @brief Base inventory. Container like object
 */
class UBaseInventory : public UInventoryAccess, public ISerializableJson {
    GENERATED_BODY()

  public:
    UBaseInventory();

    UFUNCTION(BlueprintCallable)
    void Empty();

    UFUNCTION(BlueprintCallable)
    void clear() override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    bool Equal(const UBaseInventory *other) const;

    virtual void Sanitize() override;

    virtual int64 add_with_limit(const FItemData &other) override;

  public:
    virtual TSubclassOf<UBaseInventoryWidgetBase>
    GetWidgetClass() const override;

    UFUNCTION(BlueprintCallable)
    virtual void SetWidgetClass(TSubclassOf<UInventoryWidgetBase> widget_class);

    void SetFilter(UInventoryFilter *filter);

    UInventoryFilter *GetFilter();

    void SetMaxSlotFunctor(TFunction<int64(const FItemData &)> func);

  public:
    virtual int32 min() const override;

    virtual int32 max() const override;

    virtual int32 find(const UItem *item) const override;

    virtual const FItemData &safe_get(int32 index) const override;

    UFUNCTION(BlueprintCallable)
    virtual bool IsEmpty() const override;

    virtual int64 sum(const UItem *item) const override;

    virtual const FItemData &get(int32 index) const override;

    virtual int64 GetSlotCapacity(int32 index) const override;

    virtual int32 size() const override;

    virtual int64 add(const FItemData &other) override;

    virtual int64 add_to(int32 index, const FItemData &other) override;

    virtual int64 sub(const FItemData &other) override;

    virtual int64 sub_from(int32 index, const FItemData &other) override;

  protected:
    bool CheckFilter(const FItemData &data);

    void ClearSlot(int32 index);

  protected:
    UPROPERTY(
        VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")
    )
    TArray<FItemData> mData;

    UPROPERTY(
        VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")
    )
    UInventoryFilter *mFilter;

    UPROPERTY(
        VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")
    )
    TSubclassOf<UBaseInventoryWidgetBase> mWidgetClass;

    TFunction<int64(const FItemData &)> mMaxSlotCount;

    bool mAutoSize = false;

    FItemData lua_get_slot(int32 index);
    int32 lua_get_count();

  public:
    EVO_LUA_CODEGEN_DB(UBaseInventory, BaseInventory);
    static void RegisterLua(lua_State *L);
};
