// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "Evospace/Blocks/BlockDeserializeLegacyLuaState.h"
#include "Evospace/Common.h"
#include "Evospace/Item/ItemLogic.h"
#include "Evospace/SerializableJson.h"

#include <Engine/World.h>
#include <Internationalization/Text.h>
#include <Math/TransformNonVectorized.h>
#include <Templates/SubclassOf.h>

#include "static_item.generated.h"

struct FItemData;
class UUserWidgetSlot;
class AItemLogic;

/** \file static_item.h
 *  \brief Recipe
 *   
 *   Details.
 */

/** @def UStaticItem
 *  @brief 
 */

UCLASS(BlueprintType)
class UStaticItem : public UObject, public ISerializableJson {
    GENERATED_BODY()

    // Lua api
  public:
    /**
     * @brief 
     * @return 
     */
    UTexture2D *get_image() const { return mImage; }

    /**
     * @brief 
     * @param val 
     */
    void set_image(UTexture2D *val) { mImage = val; }

    /**
     * @brief 
     * @return 
     */
    float get_unit_mul() const { return mUnitMul; }

    /**
     * @brief 
     * @param val 
     */
    void set_unit_mul(float val) { mUnitMul = val; }

    /**
     * @brief 
     * @return 
     */
    int64 get_max_count() const { return mMaxCount; }

    /**
     * @brief 
     * @param val 
     */
    void set_max_count(int64 val) { mMaxCount = val; }

    /**
     * @brief 
     * @return 
     */
    UStaticMesh *get_mesh() const { return mMesh; }

    /**
     * @brief 
     * @param val 
     */
    void set_mesh(UStaticMesh *val) { mMesh = val; }

    /**
     * @brief Object name in database
     */
    std::string name;

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

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool mStackable = true;

    TSharedPtr<FJsonObject> mLogicJson;

    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    FText GetLabel() const;

    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    FText GetDescription() const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool mSolid = true;
};
