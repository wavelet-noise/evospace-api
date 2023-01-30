// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "../SerializableJson.h"
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/item_data.h"
#include "Evospace/Shared/Core/prototype.h"
#include "Evospace/Shared/Vanilla/inventory_access.h"
#include "InventoryWidget.h"

#include <Templates/Function.h>
#include <Templates/SubclassOf.h>

#include "BaseInventory.generated.h"

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

    virtual int64 _AddWithLimit(const FItemData &other) override;

  public:
    virtual TSubclassOf<UBaseInventoryWidgetBase>
    GetWidgetClass() const override;

    UFUNCTION(BlueprintCallable)
    virtual void SetWidgetClass(TSubclassOf<UInventoryWidgetBase> widget_class);

    void SetFilter(UInventoryFilter *filter);

    UInventoryFilter *GetFilter();

    void SetMaxSlotFunctor(TFunction<int64(const FItemData &)> func);

  public:
    virtual int32 _Min() const override;

    virtual int32 _Max() const override;

    virtual int32 _Find(const UItem *item) const override;

    virtual int32 _FindEmpty() const override;

    virtual int32 _FindNotEmpty() const override;

    const FItemData &_SafeGet(int32 index) const;

    UFUNCTION(BlueprintCallable)
    virtual bool IsEmpty() const override;

    virtual int64 _Sum(const UItem *item) const override;

    virtual const FItemData &_Get(int32 index) const override;

    virtual int64 GetSlotCapacity(int32 index) const override;

    virtual int32 _Num() const override;

    virtual int64 _Add(const FItemData &other) override;

    virtual int64 _Add(int32 index, const FItemData &other) override;

    virtual int64 _Sub(const FItemData &other) override;

    virtual int64 _Sub(int32 index, const FItemData &other) override;

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
