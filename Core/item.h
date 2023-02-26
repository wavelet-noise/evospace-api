// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "Core/loc.h"
#include "Core/prototype.h"
#include "Evospace/Blocks/BlockDeserializeLegacyLuaState.h"
#include "Evospace/Item/ItemLogicActor.h"
#include "Evospace/SerializableJson.h"

#include <Engine/World.h>
#include <Internationalization/Text.h>
#include <Math/TransformNonVectorized.h>
#include <Templates/SubclassOf.h>

#include <vector>

#include "item.generated.h"

struct FItemData;
class UUserWidgetSlot;
class AItemLogicActor;

UCLASS(BlueprintType)
/**
 * @brief Static part of every item
 *
 * FItemData {
 *      count: per instance data,
 *      item: static part pointer
 * }
 *
 * Not modifiable in game part of item
 */
class UItem : public UPrototype, public ISerializableJson {
    GENERATED_BODY()

    // Lua api
  public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    /**
     * @brief Property. Item ico for drawing in inventory
     *
     * Default value: nil
     *
     * @code{.lua}
     * local coal = Item.get("Coal")
     * image = coal.image
     * coal.image = image
     * @endcode
     */
    UTexture2D *image = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    /**
     * @brief Property. Multiplier for internal item count units
     *
     * When drawing in inventory this multiplier is applying. Showing number =
     * count * multiplier
     *
     * Default value: 1.0
     *
     * @code{.lua}
     * local coal = Item.get("Coal")
     * mul = coal.unit_mul
     * coal.unit_mul = 1.0
     * @endcode
     */
    float unit_mul = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    /**
     * @brief Property. Max count that can be stored in one slot of default
     * inventory
     *
     * Default value: 0
     *
     * @code{.lua}
     * local coal = Item.get("Coal")
     * count = coal.max_count
     * coal.max_count = 64
     * @endcode
     */
    int64 max_count = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    /**
     * @brief Property. Mesh for rendering item in world (on ground or at
     * conveyor)
     */
    UStaticMesh *mesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    /**
     * @brief Set visibility for non creative game
     */
    bool craftable = true;

    /**
     * @brief KeyTable array with (Key, Table) pairs.
     *
     * ("Copper", "misc")
     * ("Sign", "blocks")
     */
    std::vector<KeyTable> label_parts = {};

    // Database page tag
    std::string page = "";

    std::string category = "";

    // Description common keys
    std::vector<KeyTable> description_parts = {};

    /**
     * @brief 
     * @param kt 
     */
    void append_description(const KeyTable &kt);

    /**
     * @brief 
     * @param kt 
     */
    void append_label(const KeyTable &kt);

    KeyTable label_format;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    const UItemLogic *logic;

    // Engine code
  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    AItemLogicActor *
    SpawnLogicItemDeferred(UWorld *world, const FTransform &transform) const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<UMaterialInterface *> mMaterials;

    // In-game effects color
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FLinearColor mColor = FLinearColor(.5, .5, .5, 1);

    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    FText GetLabel() const;

    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    FText GetDescription() const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool mSolid = true;

  public:
    EVO_LUA_CODEGEN_DB(UItem, Item);
    static void lua_reg(lua_State *L);
};
