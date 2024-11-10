// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "EvospaceLuaState.h"
#include "Public/BlockLogic.h"
#include "LuaState.h"

namespace evo {
/**
 * @brief Legacy lua state for BlockLogic lua script part executing
 */
class LegacyLuaState : public ModLoadingLuaState {
  public:
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

  static int Accessor_bind_resource(lua_State *l);

  static int Crafter_get_resource_component(lua_State *l);

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

  static int BlockLogic_new_resource_accessor(lua_State *l);

  /**
     * @brief Create new accessor for crafter
     * @details lua syntax
     * @code{.lua}
     * crafter:create_accessor(get_class("KineticInputAccessor"))
     * @endcode
     * @param type
     * @return Constructed accessor object with given type
     */
  static int BlockLogic_new_item_accessor(lua_State *l);

  void SetCurrent(AActor *actor);
  void SetCurrent(UBlockLogic *actor);

  virtual void Init() override;

  AActor *current_object;
};
} // namespace evo