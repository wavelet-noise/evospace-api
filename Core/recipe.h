// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "Evospace/SerializableJson.h"
#include "Core/item_data.h"

#include <Dom/JsonObject.h>

#include <string>

#include "Recipe.generated.h"

class URecipeInventory;
class UStaticResearch;

UCLASS(BlueprintType)
/**
 * @brief Item recipe data
 *
 * input inventory is must be consumed before
 * output inventory will be created
 */
class URecipe : public UObject, public ISerializableJson {
    GENERATED_BODY()

    // Lua api
  public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /**
     * @brief Property. Get recipe loss percent
     *
     * Default value: 0
     *
     */
    int32 loss = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /**
     * @brief Property. Get recipe basic duration
     *
     * Default value: 1
     *
     * @code{.lua}
     * ticks = recipe.ticks
     * recipe.ticks = 100
     * @endcode
     */
    int32 ticks = 1;

    /**
     * @brief Property. Recipe name. Must be not empty
     *
     * @code{.lua}
     * name = recipe.name
     * recipe.name = name
     * @endcode
     */
    std::string get_name() const { return TCHAR_TO_UTF8(*name.ToString()); }

    /**
     * @brief Property. Recipe name. Must be not empty
     *
     * @code{.lua}
     * name = recipe.name
     * recipe.name = name
     * @endcode
     */
    void set_name(std::string_view val) { name = UTF8_TO_TCHAR(val.data()); }

    static URecipe *lua_new() { return NewObject<URecipe>(); }

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /**
     * @brief
     */
    URecipeInventory *input;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /**
     * @brief
     */
    URecipeInventory *output;

    // Engine code
  public:
    URecipe();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FItemData res_input;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FItemData res_output;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FRecipeItemData input_data;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FRecipeItemData output_data;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName name;

    // Currently locked status (after research applying)
    // It will be better to make separate ResearchInstance object
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    mutable bool locked = false;

    // All item with research will be locked; Other items will be unlocked;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    mutable bool default_locked = false;

    // Pointer to unlocking research
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    mutable UStaticResearch *unlocks_by;

    int32 dictionary_index = INDEX_NONE;
};
