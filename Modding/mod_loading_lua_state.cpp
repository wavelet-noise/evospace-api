// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#include "mod_loading_lua_state.h"

#include "Evospace/Blocks/BaseInventorySideAccessor.h"
#include "Evospace/JsonObjectLibrary.h"
#include "Evospace/Shared/Core/recipe.h"
#include "Evospace/Shared/Core/recipe_dictionary.h"

namespace evo {
ModLoadingLuaState::ModLoadingLuaState() {

    using namespace luabridge;

    getGlobalNamespace(L).addFunction(
        "register", &ModLoadingLuaState::RegisterObject
    );

    getGlobalNamespace(L)
        .beginClass<URecipe>("Recipe")
        .addProperty("loss", &URecipe::get_loss, &URecipe::set_loss)
        .addProperty("ticks", &URecipe::get_ticks, &URecipe::set_ticks)
        .endClass();
}

void ModLoadingLuaState::RegisterObject(UObject *val) {
    ModLoadingLuaState::Get().mLibrary->RegisterObject(val);
}

inline ModLoadingLuaState &ModLoadingLuaState::Get() {
    static std::unique_ptr<ModLoadingLuaState> inst;

    if (inst == nullptr) {
        inst = std::make_unique<ModLoadingLuaState>();
    }

    return *inst;
}
} // namespace evo