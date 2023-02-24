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

  public:
    FItemData() = default;
    FItemData(const UItem *item, int64 _count);
    FItemData(const UItem *item);

    FItemData &operator=(const FItemData &val);

    bool Swap(FItemData &other);

    bool IsNull() const;

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
     * @brief
     */
    int64 capacity = 0;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    /**
     * @brief
     */
    int64 split = 1;

    bool DeserializeJson(TSharedPtr<FJsonObject> json);
};
