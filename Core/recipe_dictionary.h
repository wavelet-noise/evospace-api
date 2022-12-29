// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Evospace/SerializableJson.h"
#include "Evospace/Shared/Core/prototype.h"
#include "Evospace/Shared/Core/recipe.h"

#include "recipe_dictionary.generated.h"

class UItem;
class UInventory;
class URecipe;
class UInventoryReader;

USTRUCT(BlueprintType)
struct EVOSPACE_API FUsedIn {
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadOnly)
    const UItem *item = nullptr;

    UPROPERTY(BlueprintReadOnly)
    int32 tier = 0;
};

// UENUM(BlueprintType)
// enum class EIODirection : uint8
//{
// };

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
    int32 count() const { return mRecipes.Num(); }

    /**
     * @brief Readonly property. Get recipe from this dictionary by index
     * @code{.lua}
     * recipe = recipe_dict:recipe_at(index)
     * @endcode
     * @param index
     * @return
     */
    const URecipe *recipe_at(int32 index) const {
        if (index >= 0 && index < mRecipes.Num())
            return mRecipes[index];
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
        if (mNameChache.Contains(recipe->name))
            return false;
        mRecipes.Add(recipe);
        mNameChache.Add(recipe->name, recipe);
        return true;
    }

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
    TArray<const URecipe *> mRecipes;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<FUsedIn> mUsedIn;

    TMap<FName, const URecipe *> mNameChache;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UInventory *mUsedInInventory;

    EVO_LUA_CODEGEN_DB(URecipeDictionary, RecipeDictionary);
    static void RegisterLua(lua_State * L);
};