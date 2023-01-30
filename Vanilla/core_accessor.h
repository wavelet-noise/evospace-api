// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Blocks/InventoryAccessor.h"
#include "Evospace/Shared/Core/item_data.h"

#include "InventoryCoreAccessor.generated.h"

class UInventoryReader;
class UInventoryAccess;
class UItem;

UCLASS()
/**
 * @brief Vanilla core accessor BlockLogic
 */
class UCoreAccessor : public UBaseAccessor, public IInventoryAccessor {
    GENERATED_BODY()
  public:
    virtual UInventoryReader *GetInput() override;
    virtual UInventoryReader *GetOutput() override;

    virtual void Bind(UInventoryAccess *inventory) override;
    virtual void BindInput(UInventoryAccess *inventory) override;
    virtual void BindOutput(UInventoryAccess *inventory) override;

    void Unbind() override;
    void UnbindInput() override;
    void UnbindOutput() override;

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

  protected:
    UPROPERTY(Instanced)
    UObject *mInput;
    UPROPERTY(Instanced)
    UObject *mOutput;
};
