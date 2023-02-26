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

    // Lua api
public:
    UFUNCTION(BlueprintCallable)
    /**
     * @brief 
     */
    void clear();

    // Lua api override
public:
    virtual const FItemData &safe_get(int32 index) const override;
    virtual const FItemData &get(int32 index) const override;
    virtual int32 find(const UItem *item) const override;

    UFUNCTION(BlueprintCallable)
    virtual void reset() override;

  public:
    UBaseInventory();

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
    
    UFUNCTION(BlueprintCallable)
    virtual bool is_empty() const override;

    virtual int64 sum(const UItem *item) const override;

    virtual int64 GetSlotCapacity(int32 index) const override;

    virtual int32 size() const override;

    virtual int64 add(const FItemData &other) override;

    virtual int64 add_to(const FItemData &other, int32 index) override;

    virtual int64 sub(const FItemData &other) override;

    virtual int64 sub_from(const FItemData &other, int32 index) override;

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

    /**
     * @fn std::optional<ItemData> get(int32 index)
     * @brief Function. Get ItemData for specific BaseInventory slot
     * @param index BaseInventory slot index
     * @return ItemData from this slot or nil
     */

    std::optional<FItemData> lua_get_slot(int32 index);
    int32 lua_get_count();

  public:
    EVO_LUA_CODEGEN_DB(UBaseInventory, BaseInventory);
    static void RegisterLua(lua_State *L);
};
