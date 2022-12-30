// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#include "mod_loading_lua_state.h"

#include "Evospace/Blocks/BaseInventorySideAccessor.h"
#include "Evospace/Blocks/TieredBlockLogic.h"
#include "Evospace/IcoGenerator.h"
#include "Evospace/Item/Implementation/ObjectBuild/BaseBuildingItemLogicActor.h"
#include "Evospace/JsonObjectLibrary.h"
#include "Evospace/Item/RecipeInventory.h"
#include "Evospace/Shared/Core/auto_crafter.h"
#include "Evospace/Shared/Core/block.h"
#include "Evospace/Shared/Core/block_logic.h"
#include "Evospace/Shared/Core/crafter_base.h"
#include "Evospace/Shared/Core/prototype_classes.h"
#include "Evospace/Shared/Core/recipe.h"
#include "Evospace/Shared/Core/recipe_dictionary.h"
#include "Evospace/Shared/Core/select_crafter.h"
#include "Evospace/Tesselator/TesselatorCube.h"

#include <tuple>

namespace evo {

// namespace detail {
// template <class F, class Tuple, std::size_t... I>
// constexpr decltype(auto) apply_impl(F&& f, Tuple&& t,
// std::index_sequence<I...>)
// {
//     return std::invoke(std::forward<F>(f),
//     std::get<I>(std::forward<Tuple>(t))...);
// }
// }  // namespace detail
//
// template <class F, class Tuple>
// constexpr decltype(auto) apply(F&& f, Tuple&& t)
// {
//     return detail::apply_impl(
//         std::forward<F>(f), std::forward<Tuple>(t),
//         std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
// }

template <typename T> void registerCall(lua_State *L) {
    T::RegisterLua(L);
    T::RegisterCommonLua(L);
}

ModLoadingLuaState::ModLoadingLuaState() {

    using namespace luabridge;

    std::apply(
        [this](auto... args) {
            (evo::registerCall<
                 typename std::remove_pointer<decltype(args)>::type>(L),
             ...);
        },
        prototype_helper::classes
    );
}

ModLoadingLuaState &ModLoadingLuaState::Get() {
    static std::unique_ptr<ModLoadingLuaState> inst;

    if (inst == nullptr) {
        inst = std::make_unique<ModLoadingLuaState>();
    }

    return *inst;
}
} // namespace evo