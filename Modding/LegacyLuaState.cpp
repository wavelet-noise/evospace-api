// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#include "LegacyLuaState.h"

#include "Evospace/Blocks/Accessors/BaseInventorySideAccessor.h"
#include "Public/SelectCrafter.h"
#include "Evospace/Item/InventoryContainer.h"

using namespace luabridge;

namespace evo {
int LegacyLuaState::Accessor_bind(lua_State *l) {
  auto side_acc = Stack<UBaseInventoryAccessor *>::get(l, 1);
  auto container = Stack<UInventoryContainer *>::get(l, 2);

  side_acc.value()->Bind(container.value());

  return 0;
}

int LegacyLuaState::Crafter_get_input_container(lua_State *l) {
  auto self = Stack<UBlockLogic *>::get(l, 1);

  auto cra = Cast<USelectCrafter>(self.value());
  if (cra) {
    auto result = push(l, cra->mCrafterInputContainer);
  }

  return 1;
}

int LegacyLuaState::Crafter_get_output_container(lua_State *l) {
  auto self = Stack<UBlockLogic *>::get(l, 1);

  auto cra = Cast<USelectCrafter>(self.value());
  if (cra) {
    auto result = push(l, cra->mCrafterOutputContainer);
  }

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
  auto self = Stack<UBlockLogic *>::get(l, 1);
  auto type = Stack<UClass *>::get(l, 2);
  std::error_code ec;

  if (type && type.value()->IsChildOf(UBaseAccessor::StaticClass())) {
    auto accessor =
      NewObject<UBaseInventoryAccessor>(self.value(), type.value());
    self.value()->RegisterComponent(accessor);
    auto result = push(l, accessor);
  } else {
    auto result = push(l, LuaNil());
  }

  return 1;
}

void LegacyLuaState::SetCurrent(AActor *actor) {
  getGlobalNamespace(L).beginNamespace("Legacy").addVariable("this", actor).endNamespace();
}

void LegacyLuaState::SetCurrent(UBlockLogic *actor) {
  getGlobalNamespace(L).beginNamespace("Legacy").addVariable("this", actor).endNamespace();
}

void LegacyLuaState::Init() {
  ModLoadingLuaState::Init();
  using namespace luabridge;

  getGlobalNamespace(L).beginClass<UBlockLogic>("BlockLogic").addFunction("CreateAccessor", &LegacyLuaState::BlockLogic_create_accessor).addFunction("GetInputContainer", &LegacyLuaState::Crafter_get_input_container).addFunction("GetOutputContainer", &LegacyLuaState::Crafter_get_output_container).endClass();

  getGlobalNamespace(L)
    .deriveClass<USelectCrafter, UBlockLogic>("SelectCrafterBlockLogic")
    .endClass();

  getGlobalNamespace(L).addFunction(
    "LoadAsset", +[](std::string_view name) {
      return LoadObject<UObject>(nullptr, UTF8_TO_TCHAR(name.data()));
    });

  getGlobalNamespace(L)
    .beginClass<UBaseInventoryAccessor>("Accessor")
    .addFunction("SetSidePos", &LegacyLuaState::Accessor_set_side_pos)
    .addFunction("Bind", &LegacyLuaState::Accessor_bind)
    .endClass();

  getGlobalNamespace(L).beginClass<UInventoryContainer>("InventoryContainer").endClass();

  getGlobalNamespace(L).beginNamespace("Legacy").addVariable("this", nullptr).endNamespace();
}
} // namespace evo