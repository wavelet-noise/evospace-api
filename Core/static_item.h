// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "Evospace/Blocks/BlockModdingLuaState.h"
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

UCLASS(BlueprintType)
class EVOSPACE_API UStaticItem : public UObject, public ISerializableJson {
    GENERATED_BODY()

    // Lua api
  public:
    UTexture2D *get_image() const { return mImage; }
    void set_image(UTexture2D *val) { mImage = val; }

    float get_unit_mul() const { return mUnitMul; }
    void set_unit_mul(float val) { mUnitMul = val; }

    int64 get_max_count() const { return mMaxCount; }
    void set_max_count(int64 val) { mMaxCount = val; }

    UStaticMesh *get_mesh() const { return mMesh; }
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
