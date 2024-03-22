// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#include "EvospaceLuaState.h"
#include "PrototypeHelper.h"
#include "PrototypeInclude.h"
#include "LuaRegistration/ActorComponents.h"

#include <tuple>

namespace evo {

void ModLoadingLuaState::Init() {
  LuaState::Init();

  using namespace luabridge;

  std::apply(
    [this]<typename... Ty>(Ty... args) {
      (registerCall<std::remove_pointer_t<Ty>>(L),
       ...);
    },
    PrototypeHelper::classes);
}
} // namespace evo