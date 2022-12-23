// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/entity.h"
#include "Evospace/Shared/Core/prototype.h"
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
    FName replace_tag;

    virtual AActor *SpawnActorAndLuaDeffered(
        ADimension *world, UBlockLogic *bloc_logic, const FTransform &tr
    ) const;

    UPROPERTY(BlueprintReadOnly)
    FVector ColorSide = FVector(1);

    UPROPERTY(BlueprintReadOnly)
    FVector color_top = FVector(1);
    
    TArray<FVector3i> mPositions;

    //===================================
    
    // Transfer all block logic specific data from this block object to given block logic object
    void move_data_to_proto(evo::LuaState &state, UBlockLogic *logic);
    
    UBlockLogic *
    spawn_block(ADimension *dim, const FTransform &tr) const;

    // Spawn block dummy to occupy multiblock space. Stores parent block object 
    UPartBlockLogic *spawn_part(
        ADimension *dim, const FTransform &tr, UBlockLogic *parent
    ) const;

  private:

    std::string actor_bytecode;
    std::string block_bytecode;
    std::string tick_bytecode;

    TSharedPtr<FJsonObject> mLogicJson;

  public:
    EVO_LUA_CODEGEN(UBlock, Block);
    static std::function<void(lua_State *)> GetRegisterLambda();
};
EVO_REGISTER_STATIC(UBlock, Block);