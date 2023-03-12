// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Containers/Map.h"
#include "Core/prototype.h"
#include "Core/recipe.h"
#include "CoreMinimal.h"
#include "Evospace/SerializableJson.h"

#include "recipe_dictionary.generated.h"

class UItem;
class UInventory;
class URecipe;
class UInventoryReader;

USTRUCT(BlueprintType)
struct FUsedIn {
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadOnly)
    const UItem *item = nullptr;

    UPROPERTY(BlueprintReadOnly)
    int32 tier = 0;
};

UCLASS(BlueprintType)
/**
 * @brief List of recipes for using in some crafter
 */
class URecipeDictionary : public UPrototype, public ISerializableJson {
    GENERATED_BODY()

    // Lua api
  public:
    /**
     * @brief Readonly property. Count of recipes in this dictionary
     * @code{.lua}
     * recipe = recipe_dict:count()
     * @endcode
     * @return
     */
    int32 count() const { return recipes.Num(); }

    /**
     * @brief Readonly property. Get recipe from this dictionary by index
     * @code{.lua}
     * recipe = recipe_dict:recipe_at(index)
     * @endcode
     * @param index
     * @return
     */
    const URecipe *recipe_at(int32 index) const {
        if (index >= 0 && index < recipes.Num())
            return recipes[index];
        return nullptr;
    }

    /**
     * @brief Add recipe to this dictionary
     * @code{.lua}
     * success = recipe_dict:add_recipe(recipe)
     * @endcode
     * @param recipe
     * @return false if recipe is already in dictionary, true otherwise
     */
    bool add_recipe(URecipe *recipe) {
        if (name_cache.Contains(recipe->name)) {
            LOG(ERROR_LL) << "RecipeDictionary is already contains "
                          << TCHAR_TO_UTF8(*recipe->name.ToString());
            return false;
        }
        recipes.Add(recipe);
        name_cache.Add(recipe->name, recipe);
        recipe->dictionary_index = recipes.Num() - 1;
        return true;
    }

    bool add_used_in(UItem *item);

    /**
     * @brief Create new instance of RecipeDictionary
     * @code{.lua}
     * recipe_dict = RecipeDictionary.new()
     * @endcode
     * @return
     */
    static URecipeDictionary *_new() { return NewObject<URecipeDictionary>(); }

    // Engine code
  public:
    URecipeDictionary();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    const URecipe *Find(UInventoryReader *inventory) const;
    int32 FindIndex(UInventoryReader *inventory) const;

    UFUNCTION(BlueprintCallable)
    TArray<URecipe *> &GetRecipes();

    const TArray<const URecipe *> &GetRecipes() const;

    const TArray<FUsedIn> &GetUsedIn() const;

    const URecipe *GetByName(const FName &name) const;

    UInventory *GetUsedInInventory();

    void ResetLocked();

    const URecipe *Find(const UItem *item, int32 count = 1) const;

  public:
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<const URecipe *> recipes;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<FUsedIn> used_in;

    // ReSharper disable once CppUE4ProbableMemoryIssuesWithUObjectsInContainer
    TMap<FName, const URecipe *> name_cache;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UInventory *mUsedInInventory;

    EVO_LUA_CODEGEN_DB(URecipeDictionary, RecipeDictionary);
    static void lua_reg(lua_State *L);
};