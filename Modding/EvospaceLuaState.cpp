// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#include "EvospaceLuaState.h"
#include "PrototypeHelper.h"
#include "PrototypeInclude.h"
#include "LuaRegistration/ActorComponents.h"

#include <tuple>

namespace evo {

void RegisterClassAndSuper(UClass *Class, TSet<UClass *> &Registered, lua_State *L) {
  if (!Class || Registered.Contains(Class)) {
    return;
  }

  // Register superclass first
  auto super = Class->GetSuperClass();
  if (super && super != Class && super->IsChildOf(UPrototype::StaticClass())) {
    RegisterClassAndSuper(Class->GetSuperClass(), Registered, L);
  }

  if (const auto cdo = Class->GetDefaultObject<UPrototype>()) {
  if (!Registered.Contains(cdo->lua_reg_type())) {
      cdo->lua_reg_internal(L);
      cdo->lua_reg(L);
      Registered.Add(Class);
    }
  }
}

void ModLoadingLuaState::Init() {
  LuaState::Init();

  TSet<UClass *> registered = {};
  for (TObjectIterator<UClass> it; it; ++it) {
    if (it->IsChildOf(UPrototype::StaticClass()) && !registered.Contains(*it)) {
      RegisterClassAndSuper(*it, registered, L);
    }
  }
}
} // namespace evo