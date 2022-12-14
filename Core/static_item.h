// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "Evospace/Blocks/BlockDeserializeLegacyLuaState.h"
#include "Evospace/Common.h"
#include "Evospace/Item/ItemLogic.h"
#include "Evospace/SerializableJson.h"
#include "Evospace/Shared/bases.h"

#include <Engine/World.h>
#include <Internationalization/Text.h>
#include <Math/TransformNonVectorized.h>
#include <Templates/SubclassOf.h>

#include "static_item.generated.h"

struct FItemData;
class UUserWidgetSlot;
class AItemLogic;

UCLASS(BlueprintType)
/**
 * @brief Static part of every item
 *
 * Item Instance {
 *      per instance data,
 *      static part pointer
 * }
 *
 * Not modifiable part of item
 */
class UStaticItem : public UObject,
                    public ISerializableJson,
                    public evo::BaseHelper<UStaticItem> {
    GENERATED_BODY()

    // Lua api
  public:
    /**
     * @brief Get item ico for drawing in inventory
     * @code{.lua}
     * image = static_item.image()
     * @endcode
     * @return Texture2D object
     */
    UTexture2D *get_image() const { return mImage; }

    /**
     * @brief Set item ico for drawing in inventory
     * @code{.lua}
     * static_item.image = image
     * @endcode
     * @param tex Texture2D object
     */
    void set_image(UTexture2D *tex) { mImage = tex; }

    /**
     * @brief Get multiplier for internal item count units
     *
     * When drawing in inventory this multiplier is applying. Showing number =
     * count * multiplier
     *
     * @code{.lua}
     * mul = static_item.unit_mul()
     * @endcode
     * @return multiplier
     */
    float get_unit_mul() const { return mUnitMul; }

    /**
     * @brief Set multiplier for internal item count units
     *
     * When drawing in inventory this multiplier is applying. Showing number =
     * count * multiplier
     * @code{.lua}
     * static_item.unit_mul = mul
     * @endcode
     * @param mul multiplier
     */
    void set_unit_mul(float mul) { mUnitMul = mul; }

    /**
     * @brief Get max count that can be stored in one slot of default inventory
     * @return
     */
    int64 get_max_count() const { return mMaxCount; }

    /**
     * @brief Set max count that can be stored in one slot of default inventory
     * @param max count
     */
    void set_max_count(int64 max) { mMaxCount = max; }

    /**
     * @brief Get mesh for rendering item in world (on ground or at conveyor)
     * @return mesh object
     */
    UStaticMesh *get_mesh() const { return mMesh; }

    /**
     * @brief Set mesh for rendering item in world (on ground or at conveyor)
     * @param mesh
     */
    void set_mesh(UStaticMesh *mesh) { mMesh = mesh; }

    /**
     * @brief Set visibility for non creative game
     * @return mesh object
     */
    bool get_craftable() const { return mCraftable; }

    /**
     * @brief Get visibility for non creative game
     * @param craftable
     */
    void set_craftable(bool craftable) { mCraftable = craftable; }

    // Engine code
  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    AItemLogic *
    SpawnLogicItemDeffered(UWorld *world, const FTransform &transform) const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FKeyTableObject> mLabelParts = {};

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FKeyTableObject mLabelFormat;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float mUnitMul = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTexture2D *mImage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<AItemLogic> mItemLogic;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UStaticMesh *mMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<UMaterialInterface *> mMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int64 mMaxCount = 0;

    // Database page tag
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName mTag = "";

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName mCategory = "";

    // Description common keys
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FKeyTableObject> mDescriptionParts = {};

    // Ingame effects color
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FLinearColor mColor = FLinearColor(.5, .5, .5, 1);

    // Hidden in survival
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool mCraftable = true;

    TSharedPtr<FJsonObject> mLogicJson;

    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    FText GetLabel() const;

    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    FText GetDescription() const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool mSolid = true;

    static std::function<void(lua_State *)> GetRegisterLambda();
};
EVO_REGISTER_STATIC(UStaticItem, StaticItem);
