// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "Containers/Array.h"
#include "Core/item_data.h"
#include "Vanilla/inventory.h"

#include <Dom/JsonObject.h>
#include <Templates/SharedPointer.h>
#include <Templates/SubclassOf.h>

#include "recipe_inventory.generated.h"

class URecipe;

UCLASS(BlueprintType)
class URecipeInventory : public UInternalInventory {
    GENERATED_BODY()

  public:
    virtual void SortKeyAZ() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FRecipeItemData> mRecipeData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    URecipe *mRecipe;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual TSubclassOf<UBaseInventoryWidgetBase>
    GetWidgetClass() const override;

    static int32 Add(URecipeInventory *from, const FItemData &other);

  public:
    EVO_LUA_CODEGEN_DB(URecipeInventory, RecipeInventory);
    static void RegisterLua(lua_State *L);
};