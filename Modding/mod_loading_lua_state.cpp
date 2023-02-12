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

ModLoadingLuaState::~ModLoadingLuaState() {
    std::apply(
        [this](auto... args) {
            (clearCall<typename std::remove_pointer<decltype(args)>::type>(L),
             ...);
        },
        evo::prototype_helper::classes
    );
}
} // namespace evo