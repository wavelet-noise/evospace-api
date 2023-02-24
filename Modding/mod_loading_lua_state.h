// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/database.h"
#include "CoreMinimal.h"
#include "lua_state.h"

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
        T::lua_reg(L);
        T::lua_reg_internal(L);
    }
    template <typename T> void clearCall(lua_State *L) { evo::DB::clear<T>(); }
};
} // namespace evo