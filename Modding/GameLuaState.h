// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "LegacyLuaState.h"

class ULuaBlock;
class UJsonObjectLibrary;

namespace evo {
/**
 * @brief World tick lua state for BlockLogic lua script part executing
 */
class GameLuaState : public LuaState {
  public:
  GameLuaState();

  private:
  template <typename T>
  void registerCall(lua_State *L) {
    T::lua_reg(L);
    T::lua_reg_internal(L);
  }
};
} // namespace evo