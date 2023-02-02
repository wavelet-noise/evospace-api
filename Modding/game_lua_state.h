// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "legacy_lua_state.h"

class ULuaBlock;
class UPrototype;
class UJsonObjectLibrary;

namespace evo {
/**
 * @brief World tick lua state for BlockLogic lua script part executing
 */
class GameLuaState : public LuaState {
  public:
    GameLuaState();

    static GameLuaState &Get();

  private:
    UJsonObjectLibrary *mLibrary = nullptr;
};
} // namespace evo