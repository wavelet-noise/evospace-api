#include "prototype.h"

void UPrototype::lua_postprocess(ModLoadingContext &context){
}

void UPrototype::RegisterLua(lua_State *L) {
    luabridge::getGlobalNamespace(L)
        .beginClass<UPrototype>("Prototype")
        .addProperty("name", &UPrototype::name, false)
        .endClass();
}