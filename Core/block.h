// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Core/entity.h"
#include "Core/prototype.h"
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
class UTesselator;

UCLASS(BlueprintType)
/**
 * @brief Block in world. Can be cube, machine or smooth surface segment
 */
class UBlock : public UEntity {
    GENERATED_BODY()

    // Lua api
  public:
    UPROPERTY(BlueprintReadWrite)
    /**
     * @brief Object for this block in inventory
     */
    const UItem *item;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Object for this block in dimension logics
     */
    const UBlockLogic *logic;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Object for this block in sector mesh
     */
    const UTesselator *tesselator;

    UPROPERTY()
    /**
     * @brief Object for this block in user view as BlockActor
     */
    UClass *actor = nullptr;

    UPROPERTY()
    /**
     * @brief Object for this block while building by player
     */
    UClass *selector = nullptr;

    /**
     * @brief Block replace tag
     */
    std::string replace_tag;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Color on sides of this block in sector mesh, while it is a surface
     */
    FVector color_side = FVector(1);

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Color on top of this block in sector mesh, while it is a surface
     */
    FVector color_top = FVector(1);

    /**
     * @brief All sub cells for this block object in dimension logics
     */
    std::vector<FVector3i> sub_blocks;

    // Engine code
  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    const UTesselator *GetTesselator() const;

    virtual AActor *SpawnActorAndLuaDeferred(
        ADimension *world, UBlockLogic *bloc_logic, const FTransform &tr
    ) const;

    //===================================

    UBlockLogic *spawn_block(ADimension *dim, const FTransform &tr) const;

    // Spawn block dummy to occupy multiblock space. Stores parent block object
    UPartBlockLogic *spawn_part(
        ADimension *dim, const FTransform &tr, UBlockLogic *parent
    ) const;

  public:
    EVO_LUA_CODEGEN_DB_EX(Block);
    static void RegisterLua(lua_State *L);
};