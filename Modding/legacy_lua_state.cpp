// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#include "legacy_lua_state.h"

#include "Core/base_inventory_accessor.h"
#include "Core/block_logic.h"
#include "Core/select_crafter.h"
#include "Vanilla/inventory_container.h"

using namespace luabridge;

namespace evo {
LegacyLuaState::LegacyLuaState() {

    using namespace luabridge;

    getGlobalNamespace(L)
        .beginClass<USelectCrafter>("BlockLogic")
        .addFunction(
            "create_accessor", &LegacyLuaState::BlockLogic_create_accessor
        )
        .addFunction(
            "get_input_container", &LegacyLuaState::Crafter_get_input_container
        )
        .addFunction(
            "get_output_container",
            &LegacyLuaState::Crafter_get_output_container
        )
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UBaseInventoryAccessor>("Accessor")
        .addFunction("set_side_pos", &LegacyLuaState::Accessor_set_side_pos)
        .addFunction("bind", &LegacyLuaState::Accessor_bind)
        .endClass();
}

int LegacyLuaState::Accessor_bind(lua_State *l) {
    auto side_acc = Stack<UBaseInventoryAccessor *>::get(l, 1);
    auto container = Stack<UInventoryContainer *>::get(l, 2);

    side_acc.value()->Bind(container.value());

    return 0;
}

int LegacyLuaState::Crafter_get_input_container(lua_State *l) {
    auto self = Stack<USelectCrafter *>::get(l, 1);

    auto result = push(l, self.value()->mAutoCrafterInputContainer);

    return 1;
}

int LegacyLuaState::Crafter_get_output_container(lua_State *l) {
    auto self = Stack<USelectCrafter *>::get(l, 1);

    auto result = push(l, self.value()->mAutoCrafterOutputContainer);

    return 1;
}

int LegacyLuaState::Accessor_set_side_pos(lua_State *l) {
    auto self = Stack<UBaseInventoryAccessor *>::get(l, 1);
    auto side = Stack<Vec3i>::get(l, 2);
    auto pos = Stack<Vec3i>::get(l, 3);
    self.value()->SetSidePos(side.value(), pos.value());
    return 0;
}

int LegacyLuaState::BlockLogic_create_accessor(lua_State *l) {
    auto self = Stack<USelectCrafter *>::get(l, 1);
    auto type = Stack<UClass *>::get(l, 2);
    std::error_code ec;

    if (type && type.value()->IsChildOf(UBaseAccessor::StaticClass())) {
        auto accessor =
            NewObject<UBaseInventoryAccessor>(self.value(), type.value());
        self.value()->add_accessor(accessor);
        auto result = push(l, accessor);
    } else {
        auto result = push(l, luabridge::LuaNil());
    }

    return 1;
}
} // namespace evo