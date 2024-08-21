#pragma once
#include "CoreMinimal.h"
#include "Evospace/Ensure.h"
#include "Modding/Mod.h"
#include "Public/EventSystem.h"
#include "ThirdParty/lua/lua.h"

inline void registerModdingClasses(lua_State *L) {
  luabridge::getGlobalNamespace(L)
    .beginClass<UMainGameModLoader>("MainGameModLoader")
    .addFunction("reg", [](UMainGameModLoader *self, UPrototype *proto) {
      if (ensure_log(proto, u"Trying to register nullptr from " << UTF8_TO_TCHAR(self->mCurrentMod->mName.data()))) {
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

  EventSystem::lua_reg(L);
}