// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.

#pragma once

#include <Dom/JsonObject.h>
#include <Templates/SharedPointer.h>

#include "item_data.generated.h"

class UItem;

// FItemData(const UItem *item) has zero value

USTRUCT(BlueprintType)
/**
 * @brief Inventory slot data
 */
struct FItemData {
    GENERATED_BODY()

    // Lua api
  public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    /**
     * @brief Count of items in slot
     */
    int64 count = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    /**
     * @brief Item prototype object with common item fields
     */
    const UItem *item = nullptr;

    /**
     * @fn FItemData static new_empty ()
     * @brief empty ItemData constructor
     */
    // lambda in in lua_state.cpp

    /**
     * @fn FItemData static new_zero (UItem * item)
     * @brief 0 count ItemData constructor
     */
    // lambda in in lua_state.cpp

    /**
     * @fn FItemData static new (UItem * item, int64 count)
     * @brief ItemData constructor
     */
    // lambda in lua_state.cpp

  public:
    FItemData() = default;
    FItemData(const UItem *item, int64 _count);
    FItemData(const UItem *item);

    bool Swap(FItemData &other);

    FItemData &operator=(const FItemData &val);

    void Clear();

    bool operator==(const FItemData &other) const;
    bool operator!=(const FItemData &other) const;
};

USTRUCT(BlueprintType)
struct FRecipeItemData {
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    /**
     * @brief Property. Crafter output slot capacity override
     * @see USingleSlotInventory::SetCapacity
     */
    int64 capacity = 0;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    /**
     * @brief
     */
    int64 split = 1;

    bool DeserializeJson(TSharedPtr<FJsonObject> json);
};
