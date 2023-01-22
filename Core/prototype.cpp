#include "prototype.h"

void UPrototype::RegisterLua(lua_State *L) {
    luabridge::getGlobalNamespace(L)
        .beginClass<UPrototype>("Prototype")
        .addProperty("name", &UPrototype::name, false)
        .endClass();
}