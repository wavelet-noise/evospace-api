#pragma once
#include "CoreMinimal.h"
#include "Evospace/Dimension.h"
#include "ThirdParty/luabridge/luabridge.h"

inline void registerMiscClasses(lua_State *L) {
    // UOreSector
    luabridge::getGlobalNamespace(L)
        .beginClass<UOreSector>("OreSector")
        .addFunction("get_complexity", &UOreSector::get_complexity)
        .addFunction("gather_index", &UOreSector::gather_index)
        .endClass();
}
