// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/prototype.h"
#include "Evospace/Entity.h"
#include "Evospace/Tesselator/Tesselator.h"
#include "Evospace/Vector.h"

#include <UObject/ScriptInterface.h>

#include <string>

#include "block.generated.h"

namespace evo {
class LuaState;
}
class UBlockLogic;
class UPartBlockLogic;
class ADimension;

UCLASS(BlueprintType)
/**
 * @brief Block in world. Can be cube, machine or smooth surface segment
 */
class EVOSPACE_API UBlock : public UEntity {
    GENERATED_BODY()

    // Lua api
  public:
    // Engine code
  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    const UTesselator *GetTesselator() const;

    UPROPERTY(BlueprintReadWrite)
    const UItem *mStaticItem;

    UPROPERTY(BlueprintReadOnly)
    const UTesselator *mTesselator;

    UPROPERTY(BlueprintReadOnly)
    TSubclassOf<UBlockLogic> mBlockLogic;

    UPROPERTY(BlueprintReadOnly)
    TSubclassOf<AActor> mActorClass = nullptr;

    UPROPERTY(BlueprintReadOnly)
    TSubclassOf<AActor> mSelectorClass = nullptr;

    UPROPERTY(BlueprintReadOnly)
    bool mRotatable = true;

    UPROPERTY(BlueprintReadOnly)
    FName mReplaceTag;

    virtual AActor *SpawnActorAndLuaDeffered(
        ADimension *world, UBlockLogic *bloc_logic, const FTransform &tr
    ) const;

    UPROPERTY(BlueprintReadOnly)
    FVector ColorSide = FVector(1);

    UPROPERTY(BlueprintReadOnly)
    FVector ColorTop = FVector(1);

    TArray<FVector3i> mPositions;

    void MoveDataToProto(evo::LuaState &state, UBlockLogic *logic);

    //===================================

    virtual UBlockLogic *
    SpawnBlockDeffered(ADimension *dim, const FTransform &tr) const {
        return nullptr;
    }
    virtual UPartBlockLogic *SpawnPart(
        ADimension *world, const FTransform &tr, UBlockLogic *parent
    ) const;

  private:
    void to_bytecode(std::string_view str, std::string &bytecode);

    std::string actor_bytecode;
    std::string block_bytecode;
    std::string tick_bytecode;

    TSharedPtr<FJsonObject> mLogicJson;

  public:
    EVO_LUA_CODEGEN(UBlock);
    static std::function<void(lua_State *)> GetRegisterLambda();
};
EVO_REGISTER_STATIC(UBlock, StaticBlock);