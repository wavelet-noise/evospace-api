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
    
    static ModLoadingLuaState &get();

    static void clear();

  private:
    UJsonObjectLibrary *mLibrary = nullptr;
    
    template <typename T> void registerCall(lua_State *L) {
        T::RegisterLua(L);
        T::RegisterCommonLua(L);
    }

private:
    static std::unique_ptr<ModLoadingLuaState> inst;
};
} // namespace evo