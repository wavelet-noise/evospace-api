// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Core/item_data.h"
#include "Core/prototype.h"
#include "Vanilla/inventory_access.h"

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
    void RemoveAllSlots() override;

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

    virtual int32 find_empty() const override;

    virtual int32 _FindNotEmpty() const override;

    const FItemData &safe_get(int32 index) const;

    UFUNCTION(BlueprintCallable)
    virtual bool IsEmpty() const override;

    virtual int64 sum(const UItem *item) const override;

    virtual const FItemData &get(int32 index) const override;

    virtual int64 GetSlotCapacity(int32 index) const override;

    virtual int32 _Num() const override;

    virtual int64 add(const FItemData &other) override;

    virtual int64 add(int32 index, const FItemData &other) override;

    virtual int64 sub(const FItemData &other) override;

    virtual int64 sub(int32 index, const FItemData &other) override;

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

  public:
    EVO_LUA_CODEGEN_DB(UBaseInventory, BaseInventory);
    static void RegisterLua(lua_State *L);
};
