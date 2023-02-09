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
    
    virtual void LuaPostprocess(AsyncMessageObject &msg) override;

    virtual void EvospacePostDuplicate(const UBlockLogic *proto) override;

    virtual bool is_block_tick() const override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    evo::ModLoadingLuaState *parent;

    std::optional<luabridge::LuaRef> class_cache;
    std::optional<luabridge::LuaRef> cache;

    bool ready_to_tick = false;
    bool ready_to_proto_construction = false;
    bool ready_proto_clone = false;

  public:
    EVO_LUA_CODEGEN_DB_EX(LuaBlock);
    static void RegisterLua(lua_State *L);
};
