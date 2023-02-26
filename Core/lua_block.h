#pragma once
#include "Vanilla/tiered_block.h"

#include "lua_block.generated.h"

namespace evo {
class ModLoadingLuaState;
}
class USingleSlotInventory;

UCLASS()
/**
 * @brief Lua scriptable block.
 */
class ULuaBlock : public UTieredBlock {
    GENERATED_BODY()

  public:
    luabridge::LuaRef get_class_cache() const;
    luabridge::LuaRef get_cache() const;

    void set_class_cache(luabridge::LuaRef ref);
    void set_cache(luabridge::LuaRef ref);

  public:
    ULuaBlock();

    virtual void Tick() override;

    virtual void BlockBeginPlay() override;
    virtual void BlockEndPlay() override;

    virtual void lua_postprocess(ModLoadingContext &context) override;

    virtual void EvospacePostDuplicate(const UBlockLogic *proto) override;

    virtual bool is_block_tick() const override;

    void lua_state_close();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

  private:
    evo::ModLoadingLuaState *parent;

    // NEXT: luaref destructor here on reloads check liletime
    std::optional<luabridge::LuaRef> class_cache;
    std::optional<luabridge::LuaRef> cache;

    bool ready_to_tick = false;
    bool ready_proto_clone = false;

  public:
    EVO_LUA_CODEGEN_DB_EX(LuaBlock);
    static void lua_reg(lua_State *L);
};
