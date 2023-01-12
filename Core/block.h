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
class  UBlock : public UEntity {
    GENERATED_BODY()

    // Lua api
  public:
    UPROPERTY(BlueprintReadWrite)
    const UItem *item;

    UPROPERTY(BlueprintReadOnly)
    UBlockLogic *logic;

    UPROPERTY(BlueprintReadOnly)
    const UTesselator *tesselator;

    UPROPERTY()
    UClass *actor = nullptr;

    UPROPERTY()
    UClass *selector = nullptr;

    std::string replace_tag;

    // Engine code
  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    const UTesselator *GetTesselator() const;

    virtual AActor *SpawnActorAndLuaDeferred(
        ADimension *world, UBlockLogic *bloc_logic, const FTransform &tr
    ) const;

    UPROPERTY(BlueprintReadOnly)
    FVector ColorSide = FVector(1);

    UPROPERTY(BlueprintReadOnly)
    FVector color_top = FVector(1);

    std::vector<FVector3i> sub_blocks;

    //===================================

    UBlockLogic *spawn_block(ADimension *dim, const FTransform &tr) const;

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
    EVO_LUA_CODEGEN_DB(UBlock, Block);
    static void RegisterLua(lua_State *L);
};