// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/base_accessor.h"
#include "Core/base_inventory_accessor.h"
#include "Core/item_data.h"
#include "CoreMinimal.h"

#include "core_accessor.generated.h"

class UInventoryReader;
class UInventoryAccess;
class UItem;

UCLASS()
/**
 * @brief Vanilla core accessor BlockLogic
 */
class UCoreAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()
  public:
    virtual UInventoryReader *GetInput() override;
    virtual UInventoryReader *GetOutput() override;

    virtual void Bind(UInventoryAccess *inventory) override;
    virtual void BindInput(UInventoryAccess *inventory) override;
    virtual void BindOutput(UInventoryAccess *inventory) override;

    virtual void Unbind() override;
    virtual void UnbindInput() override;
    virtual void UnbindOutput() override;

    virtual bool Push(UInventoryAccess *from) override;
    virtual bool Push(UInventoryAccess *from, int32 max_count) override;
    virtual bool Push(UInventoryAccess *from, float percent) override;

    virtual bool Pop(UInventoryAccess *to) override;
    virtual bool Pop(UInventoryAccess *to, int32 max_count) override;
    virtual bool Pop(UInventoryAccess *to, float percent) override;

    virtual FItemData PopItem(UInventoryAccess *to, const UItem *item) override;
    virtual FItemData
    PopItem(UInventoryAccess *to, const FItemData &data) override;
    virtual FItemData
    PopItem(UInventoryAccess *to, const UItem *item, float percent) override;

  public:
    EVO_LUA_CODEGEN_DB_EX(CoreAccessor);
    static void lua_reg(lua_State *L);
};
