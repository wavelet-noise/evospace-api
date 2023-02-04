// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "legacy_lua_state.h"

class UJsonObjectLibrary;
namespace evo {
/**
 * @brief Legacy lua state for BlockLogic lua script part executing
 */
class ModLoadingLuaState : public LuaState {
  public:
    ModLoadingLuaState();

    static ModLoadingLuaState &Get();

  private:
    UJsonObjectLibrary *mLibrary = nullptr;

    template <typename T> void registerCall(lua_State *L) {
        T::RegisterLua(L);
        T::RegisterCommonLua(L);
    }
};
} // namespace evo