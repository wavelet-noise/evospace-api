// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "LuaState.h"

namespace evo {
/**
 * @brief Mod loading process lua state
 */
class ModLoadingLuaState : public LuaState {
  template <typename T>
  void registerCall(lua_State *L) {
    T::lua_reg(L);
    T::lua_reg_internal(L);
  }

  public:
  virtual void Init() override;
};
} // namespace evo