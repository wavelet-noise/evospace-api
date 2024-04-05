#pragma once
#include "CoreMinimal.h"
#include "Evospace/Ensure.h"
#include "Modding/Mod.h"
#include "ThirdParty/lua/lua.h"

inline void registerModdingClasses(lua_State *L) {
  luabridge::getGlobalNamespace(L)
    .beginClass<UMainGameModLoader>("MainGameModLoader")
    .addFunction("reg", [](UMainGameModLoader *self, UPrototype *proto) {
      if (ensure_log(proto, "Trying to register nullptr from " << self->mCurrentMod->mName)) {
        self->RegisterPrototype(self->mCurrentMod, proto);
      }
    })
    .addFunction("from_table", [](UMainGameModLoader *self, const luabridge::LuaRef &table) {
      self->RegisterPrototypeFromTable(self->mCurrentMod, table);
    })
    .addFunction("mod", [](UMainGameModLoader *self, const luabridge::LuaRef &table) {
      self->ModInitTable(table);
    })
    .addFunction("objects", [](UMainGameModLoader *self) {
      return self->GetPrototypes();
    })
    .endClass();
}