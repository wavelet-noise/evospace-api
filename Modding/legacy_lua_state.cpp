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
        .beginClass<Vec3i>("Vec3i")
        .addStaticFunction("new", &LegacyLuaState::Vec3i_new)
        .addStaticFunction("zero", &LegacyLuaState::Vec3i_zero)
        .addStaticFunction("up", &LegacyLuaState::Vec3i_up)
        .addStaticFunction("down", &LegacyLuaState::Vec3i_down)
        .addStaticFunction("left", &LegacyLuaState::Vec3i_left)
        .addStaticFunction("right", &LegacyLuaState::Vec3i_right)
        .addStaticFunction("back", &LegacyLuaState::Vec3i_back)
        .addStaticFunction("front", &LegacyLuaState::Vec3i_front)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UAutoCrafterBlockLogic>("BlockLogic")
        .addFunction(
            "create_accessor", &LegacyLuaState::BlockLogicCreateAccessor
        )
        .addFunction(
            "get_input_container", &LegacyLuaState::CrafterGetInputContainer
        )
        .addFunction(
            "get_output_container", &LegacyLuaState::CrafterGetOutputContainer
        )
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UBaseInventoryAccessor>("Accessor")
        .addFunction("set_side_pos", &LegacyLuaState::AccessorSetSidePos)
        .addFunction("bind", &LegacyLuaState::AccessorBind)
        .endClass();

    getGlobalNamespace(L).addFunction("get_class", &LegacyLuaState::GetClass);

    getGlobalNamespace(L)
        .beginClass<UInventoryContainer>("InventoryContainer")
        .endClass();
}

int LegacyLuaState::AccessorBind(lua_State *l) {
    auto side_acc = Stack<UBaseInventoryAccessor *>::get(l, 1);
    auto container = Stack<UInventoryContainer *>::get(l, 2);

    side_acc->Bind(container);

    return 0;
}

int LegacyLuaState::CrafterGetInputContainer(lua_State *l) {
    auto self = Stack<UAutoCrafterBlockLogic *>::get(l, 1);

    std::error_code er;

    push(l, self->mAutoCrafterInputContainer, er);

    return 1;
}

int LegacyLuaState::CrafterGetOutputContainer(lua_State *l) {
    auto self = Stack<UAutoCrafterBlockLogic *>::get(l, 1);

    std::error_code er;

    push(l, self->mAutoCrafterOutputContainer, er);

    return 1;
}

int LegacyLuaState::AccessorSetSidePos(lua_State *l) {
    auto self = Stack<UBaseInventoryAccessor *>::get(l, 1);
    auto side = Stack<Vec3i>::get(l, 2);
    auto pos = Stack<Vec3i>::get(l, 3);
    self->SetSidePos(side, pos);
    return 0;
}

Vec3i LegacyLuaState::Vec3i_new(int32 x, int32 y, int32 z) {
    return Vec3i(x, y, z);
}

Vec3i LegacyLuaState::Vec3i_zero() {
    return Vec3i(0, 0, 0);
}

Vec3i LegacyLuaState::Vec3i_one() {
    return Vec3i(1, 1, 1);
}

Vec3i LegacyLuaState::Vec3i_left() {
    return Side::Left;
}

Vec3i LegacyLuaState::Vec3i_right() {
    return Side::Right;
}

Vec3i LegacyLuaState::Vec3i_up() {
    return Side::Up;
}

Vec3i LegacyLuaState::Vec3i_down() {
    return Side::Down;
}

Vec3i LegacyLuaState::Vec3i_front() {
    return Side::Front;
}

Vec3i LegacyLuaState::Vec3i_back() {
    return Side::Back;
}

UClass *LegacyLuaState::GetClass(const std::string &name) {
    using namespace std::string_literals;
    auto type = FindObject<UClass>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        StaticLogger::Get().Log("Class not found " + name);
    }

    return type;
}

int LegacyLuaState::BlockLogicCreateAccessor(lua_State *l) {
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