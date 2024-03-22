#pragma once
#include "CoreMinimal.h"
#include "ThirdParty/lua/lua.h"

inline void registerModdingClasses(lua_State *L) {
  luabridge::getGlobalNamespace(L)
    .beginClass<UMainGameModLoader>("MainGameModLoader")
    .addFunction("reg", [](UMainGameModLoader *self, UObject *proto) {
      self->RegisterPrototype(proto);
    })
    .addFunction("from_table", [](UMainGameModLoader *self, const luabridge::LuaRef &table) {
      self->RegisterPrototypeFromTable(table);
    })
    .addFunction("mod", [](UMainGameModLoader *self, const luabridge::LuaRef &table) {
      self->ModInitTable(table);
    })
    .addFunction("objects", [](UMainGameModLoader *self) {
      return self->GetPrototypes();
    })
    .endClass();
}