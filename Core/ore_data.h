#pragma once

#include "CoreMinimal.h"

#include "ore_data.generated.h"

class UItem;

USTRUCT(BlueprintType)
struct FOreData {
    GENERATED_BODY()

    // Lua api
  public:
    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief ore Item
     */
    const UItem *item;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Item count already gathered from this OreSector
     */
    int64 gathered;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Item capacity in this OreSector on spawn
     */
    int64 capacity;

  public:
    bool SerializeJson(TSharedPtr<FJsonObject> json) const;
    bool DeserializeJson(TSharedPtr<FJsonObject> json);
};