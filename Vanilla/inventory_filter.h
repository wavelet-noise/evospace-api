// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "Core/item_data.h"

#include "inventory_filter.generated.h"

class UInventoryAccess;
class UItem;

UCLASS(Abstract, BlueprintType)
/**
 * @brief Inventory filter base class
 */
class UInventoryFilter : public UObject {
    GENERATED_BODY()

  public:
    virtual bool Check(const FItemData &data);
};

UCLASS(BlueprintType)
/**
 * @brief Inventory white filter
 */
class UInventoryWhiteFilter : public UInventoryFilter {
    GENERATED_BODY()

  public:
    virtual bool Check(const FItemData &data) override;

    void AddItem(const UItem *item);
    void Empty();

  private:
    UPROPERTY()
    TArray<const UItem *> mItems;
};

UCLASS(BlueprintType)
/**
 * @brief Inventory black filter
 */
class UInventoryBlackFilter : public UInventoryFilter {
    GENERATED_BODY()

  public:
    virtual bool Check(const FItemData &data) override;
};

UCLASS(BlueprintType)
/**
 * @brief Inventory filter by another inventory
 */
class UInventoryInventoryFilter : public UInventoryFilter {
    GENERATED_BODY()

  public:
    virtual bool Check(const FItemData &data) override;

    void SetInventory(UInventoryAccess *inv);
    UInventoryAccess *GetInventory() const;

  private:
    UPROPERTY()
    UInventoryAccess *mInventory;
};
