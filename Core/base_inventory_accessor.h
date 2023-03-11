// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once

#include "Core/base_accessor.h"
#include "Core/item_data.h"
#include "CoreMinimal.h"

#include "base_inventory_accessor.generated.h"

class UInventoryReader;
class UBaseInventoryAccessor;
class UInventoryAccess;
class UStaticIndexedItemHierarchicalInstancedStaticMeshComponent;
class UItem;

UCLASS()
class UBaseInventoryAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    UPROPERTY(VisibleAnywhere)
    bool auto_output = false;

  public:
    UBaseInventoryAccessor();

    virtual void Bind(UInventoryAccess *inventory);
    virtual void BindInput(UInventoryAccess *inventory);
    virtual void BindOutput(UInventoryAccess *inventory);

    virtual void Unbind();
    virtual void UnbindInput();
    virtual void UnbindOutput();

    bool push_to_proxy();

    virtual bool is_active() const override { return true; }

    virtual bool Push(UInventoryAccess *from);
    virtual bool Push(UInventoryAccess *from, int32 max_count);
    virtual bool Push(UInventoryAccess *from, float percent);
    virtual bool PushWithData(
        UInventoryAccess *from, int32 max_count,
        UStaticIndexedItemHierarchicalInstancedStaticMeshComponent *comp,
        int32 index
    );

    virtual bool Pop(UInventoryAccess *to);
    virtual bool Pop(UInventoryAccess *to, int32 max_count);

    virtual FItemData PopItem(UInventoryAccess *to, const UItem *item);
    virtual FItemData PopItem(UInventoryAccess *to, const FItemData &data);
    virtual FItemData
    PopItem(UInventoryAccess *to, const UItem *item, float percent);

    virtual UInventoryReader *GetInput();
    virtual UInventoryReader *GetOutput();

    template <typename _Ty> _Ty *_GetInput() { return Cast<_Ty>(mInput); }

    template <typename _Ty> _Ty *_GetOutput() { return Cast<_Ty>(mOutput); }

    virtual bool is_connectable(UBaseAccessor &acc) const override;

  protected:
    virtual void TickComponent() override;

  protected:
    UPROPERTY(VisibleAnywhere)
    UInventoryAccess *mInput;

    UPROPERTY(VisibleAnywhere)
    UInventoryAccess *mOutput;

  public:
    EVO_LUA_CODEGEN_DB_EX(BaseInventoryAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
class UDataInventoryAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()

  public:
    virtual bool Push(UInventoryAccess *from) override;
};