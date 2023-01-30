// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#include "game_lua_state.h"

#include "Evospace/Shared/Core/prototype_classes.h"
#include "Evospace/Shared/Core/prototype_includes.h"

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

namespace {
template <typename T> void registerCall(lua_State *L) {
    T::RegisterLua(L);
    T::RegisterCommonLua(L);
}
} // namespace

GameLuaState::GameLuaState() {
    std::apply(
        [this](auto... args) {
            (registerCall<typename std::remove_pointer<decltype(args)>::type>(L
             ),
             ...);
        },
        prototype_helper::classes
    );
}

GameLuaState &GameLuaState::Get() {
    static std::unique_ptr<GameLuaState> inst;

    if (inst == nullptr) {
        inst = std::make_unique<GameLuaState>();
    }

    return *inst;
}
} // namespace evo