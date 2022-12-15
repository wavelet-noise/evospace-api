// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Evospace/SerializableJson.h"
#include "Evospace/Shared/Core/recipe.h"
#include "Evospace/Shared/statics.h"

#include "recipe_dictionary.generated.h"

class UStaticItem;
class UInventory;
class URecipe;
class UInventoryReader;

USTRUCT(BlueprintType)
struct EVOSPACE_API FUsedIn {
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadOnly)
    const UStaticItem *item = nullptr;

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
class URecipeDictionary : public UObject,
                          public ISerializableJson,
                          public evo::Static {
    GENERATED_BODY()

    // Lua api
  public:
    /**
     * @brief
     * @return
     */
    int32 get_count() const { return mRecipes.Num(); }

    /**
     * @brief
     * @param index
     * @return
     */
    const URecipe *get_recipe(int32 index) const {
        if (index >= 0 && index < mRecipes.Num())
            return mRecipes[index];
        return nullptr;
    }

    /**
     * @brief
     * @param val
     * @return
     */
    bool add_recipe(URecipe *val) {
        if (mNameChache.Contains(val->name))
            return false;
        mRecipes.Add(val);
        mNameChache.Add(val->name, val);
        return true;
    }

    /**
     * @brief
     * @return
     */
    static URecipeDictionary *new_object() {
        return NewObject<URecipeDictionary>();
    }

    // Engine code
  public:
    URecipeDictionary();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    const URecipe *Find(UInventoryReader *inventory) const;

    UFUNCTION(BlueprintCallable)
    TArray<URecipe *> &GetRecipes();

    const TArray<const URecipe *> &GetRecipes() const;

    const TArray<FUsedIn> &GetUsedIn() const;

    const URecipe *GetByName(const FName &name) const;

    UInventory *GetUsedInInventory();

    void ResetLocked();

    const URecipe *Find(const UStaticItem *item, int32 count = 1) const;

  public:
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<const URecipe *> mRecipes;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<FUsedIn> mUsedIn;

    TMap<FName, const URecipe *> mNameChache;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UInventory *mUsedInInventory;

    static std::function<void(lua_State *)> GetRegisterLambda();
};
EVO_REGISTER_STATIC(URecipeDictionary, RecipeDictionary);