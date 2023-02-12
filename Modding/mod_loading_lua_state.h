// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "lua_state.h"
#include "Core/database.h"

namespace evo {
/**
 * @brief Mod loading process lua state
 */
class ModLoadingLuaState : public LuaState {
  public:
    ModLoadingLuaState();
    virtual ~ModLoadingLuaState() override;

  private:
    template <typename T> void registerCall(lua_State *L) {
        T::RegisterLua(L);
        T::RegisterCommonLua(L);
    }
    template <typename T> void clearCall(lua_State *L) { evo::DB::clear<T>(); }
};
} // namespace evo