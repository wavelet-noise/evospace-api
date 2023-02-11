// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#include "mod_loading_lua_state.h"

#include "Core/prototype_classes.h"
#include "Core/prototype_includes.h"

#include <tuple>

namespace evo {
ModLoadingLuaState::ModLoadingLuaState() {
    std::apply(
        [this](auto... args) {
            (registerCall<typename std::remove_pointer<decltype(args)>::type>(L
             ),
             ...);
        },
        prototype_helper::classes
    );
}

ModLoadingLuaState &ModLoadingLuaState::get() {
    if (inst == nullptr) {
        inst = std::make_unique<ModLoadingLuaState>();
    }

    return *inst;
}

void ModLoadingLuaState::clear(){
    if (inst and inst->L) {
        lua_close(inst->L);
        inst->L = nullptr;
        inst = nullptr;
    }
}

std::unique_ptr<ModLoadingLuaState> ModLoadingLuaState::inst = nullptr;
} // namespace evo