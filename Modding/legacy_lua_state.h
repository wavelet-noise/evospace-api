// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/CoordinateSystem.h"
#include "lua_state.h"

#include <string>

namespace evo {
/**
 * @brief Legacy lua state for BlockLogic lua script part executing
 */
class LegacyLuaState : public LuaState {
  public:
    LegacyLuaState();

    /**
     * @brief Bind inventory to accessor
     * @details lua syntax
     * @code{.lua}
     * accessor:bind(crafter:get_input_container())
     * @endcode
     * @param inventory
     * @return Nothing
     */
    static int Accessor_bind(lua_State *l);

    /**
     * @brief Get input container from crafter
     * @details lua syntax
     * @code{.lua}
     * crafter:get_input_container()
     * @endcode
     * @return InventoryContainer object
     */
    static int Crafter_get_input_container(lua_State *l);

    /**
     * @brief Get output container from crafter
     * @details lua syntax
     * @code{.lua}
     * crafter:get_output_container()
     * @endcode
     * @return InventoryContainer object
     */
    static int Crafter_get_output_container(lua_State *l);

    /**
     * @brief Setup accessor side and position
     * @details lua syntax
     * @code{.lua}
     * accessor:set_side_pos(Vec3i.right(), Vec3i.one())
     * @endcode
     * @param side
     * @param pos
     * @return Nothing
     */
    static int Accessor_set_side_pos(lua_State *l);

    /**
     * @brief Create new accessor for crafter
     * @details lua syntax
     * @code{.lua}
     * crafter:create_accessor(get_class("KineticInputAccessor"))
     * @endcode
     * @param type
     * @return Constructed accessor object with given type
     */
    static int BlockLogic_create_accessor(lua_State *l);
};
} // namespace evo