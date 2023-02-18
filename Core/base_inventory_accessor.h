// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
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

    bool Push();

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
    virtual bool Pop(UInventoryAccess *to, float percent);

    virtual FItemData PopItem(UInventoryAccess *to, const UItem *item);
    virtual FItemData PopItem(UInventoryAccess *to, const FItemData &data);
    virtual FItemData
    PopItem(UInventoryAccess *to, const UItem *item, float percent);

    virtual UInventoryReader *GetInput();
    virtual UInventoryReader *GetOutput();

    template <typename _Ty> _Ty *_GetInput() { return Cast<_Ty>(mInput); }

    template <typename _Ty> _Ty *_GetOutput() { return Cast<_Ty>(mOutput); }

  protected:
    virtual void TickComponent() override;

    virtual UBaseInventoryAccessor *GetAutoOutsideAccessor();

  protected:

    UPROPERTY(VisibleAnywhere)
    UObject *mInput;

    UPROPERTY(VisibleAnywhere)
    UObject *mOutput;

  public:
    EVO_LUA_CODEGEN_DB_EX(BaseInventoryAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
class UDataInventoryAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()

  public:
    virtual bool Push(UInventoryAccess *from) override;
};