// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "Evospace/Item/ItemData.h"
#include "Evospace/SerializableJson.h"

#include <Dom/JsonObject.h>


#include <string>

#include "Recipe.generated.h"

class URecipeInventory;
class UStaticResearch;

UCLASS(BlueprintType)
/**
 * @brief 
 */
class EVOSPACE_API URecipe : public UObject, public ISerializableJson {
    GENERATED_BODY()

    // Lua api
  public:
    /**
     * @brief 
     * @return 
     */
    int32 get_loss() const { return loss; }

    /**
     * @brief 
     * @param val 
     */
    void set_loss(int32 val) { loss = val; }

    /**
     * @brief 
     * @return 
     */
    int32 get_ticks() const { return ticks; }

    /**
     * @brief 
     * @param val 
     */
    void set_ticks(int32 val) { ticks = val; }

    // Engine code
  public:
    
    URecipe();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    URecipeInventory *input;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    URecipeInventory *output;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FItemData res_input;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FItemData res_output;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FRecipeItemData input_data;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FRecipeItemData output_data;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 ticks = 1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 loss = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName name;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    mutable bool locked = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    mutable bool default_locked = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    mutable UStaticResearch *unlocks_by;
};
