#pragma once
#include "Vanilla/tiered_block.h"

#include "lua_block.generated.h"

namespace evo {
class GameLuaState;
}
class USingleSlotInventory;

UCLASS()
class ULuaBlock : public UBlockLogic {
    GENERATED_BODY()

  public:
    std::optional<luabridge::LuaRef> self_static;
    std::optional<luabridge::LuaRef> tick_static;
    std::optional<luabridge::LuaRef> self;

  public:
    ULuaBlock();

    virtual void Tick() override;

    virtual void BlockBeginPlay() override;
    virtual void BlockEndPlay() override;

    virtual void LuaPrepare() override;
    virtual void LuaPostprocess() override;

    virtual void EvospacePostDuplicate(const UBlockLogic *proto) override;

    virtual bool is_block_tick() const override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    evo::GameLuaState *parent;

    bool ready_to_tick = false;

  public:
    EVO_LUA_CODEGEN_DB_EX(LuaBlock);
    static void RegisterLua(lua_State *L);
};
