#include "legacy_lua_state.h"

#include "Evospace/Blocks/AutoCrafterBlockLogic.h"
#include "Evospace/Blocks/BaseInventorySideAccessor.h"
#include "Evospace/Blocks/BlockLogic.h"
#include "Evospace/Item/BaseInventory.h"
#include "Evospace/Item/InventoryContainer.h"
#include "Evospace/Shared/static_logger.h"

using namespace luabridge;

namespace evo {
LegacyLuaState::LegacyLuaState() {

    getGlobalNamespace(L)
        .beginClass<UObject>("Object")
        //.addFunction("ptr", &UBlockModdingLuaState::LuaThis)
        .endClass();

    getGlobalNamespace(L).beginClass<UClass>("Class").endClass();

    getGlobalNamespace(L)
        .beginClass<UAutoCrafterBlockLogic>("BlockLogic")
        .addFunction(
            "create_accessor", &LegacyLuaState::BlockLogic_create_accessor
        )
        .addFunction(
            "get_input_container", &LegacyLuaState::Crafter_get_input_container
        )
        .addFunction(
            "get_output_container", &LegacyLuaState::Crafter_get_output_container
        )
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UBaseInventoryAccessor>("Accessor")
        .addFunction("set_side_pos", &LegacyLuaState::Accessor_set_side_pos)
        .addFunction("bind", &LegacyLuaState::Accessor_bind)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UInventoryContainer>("InventoryContainer")
        .endClass();
}

int LegacyLuaState::Accessor_bind(lua_State *l) {
    auto side_acc = Stack<UBaseInventoryAccessor *>::get(l, 1);
    auto container = Stack<UInventoryContainer *>::get(l, 2);

    side_acc->Bind(container);

    return 0;
}

int LegacyLuaState::Crafter_get_input_container(lua_State *l) {
    auto self = Stack<UAutoCrafterBlockLogic *>::get(l, 1);

    std::error_code er;

    push(l, self->mAutoCrafterInputContainer, er);

    return 1;
}

int LegacyLuaState::Crafter_get_output_container(lua_State *l) {
    auto self = Stack<UAutoCrafterBlockLogic *>::get(l, 1);

    std::error_code er;

    push(l, self->mAutoCrafterOutputContainer, er);

    return 1;
}

int LegacyLuaState::Accessor_set_side_pos(lua_State *l) {
    auto self = Stack<UBaseInventoryAccessor *>::get(l, 1);
    auto side = Stack<Vec3i>::get(l, 2);
    auto pos = Stack<Vec3i>::get(l, 3);
    self->SetSidePos(side, pos);
    return 0;
}



int LegacyLuaState::BlockLogic_create_accessor(lua_State *l) {
    auto self = Stack<UAutoCrafterBlockLogic *>::get(l, 1);
    auto type = Stack<UClass *>::get(l, 2);
    std::error_code ec;

    if (type && type->IsChildOf(UBaseAccessor::StaticClass())) {
        auto accessor = NewObject<UBaseInventoryAccessor>(self, type);
        self->RegisterComponent(accessor);
        push(l, accessor, ec);
    } else {
        push(l, luabridge::LuaNil(), ec);
    }

    return 1;
}
} // namespace evo