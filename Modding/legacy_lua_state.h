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

    static int AccessorBind(lua_State *l);

    static int CrafterGetInputContainer(lua_State *l);

    static int CrafterGetOutputContainer(lua_State *l);

    static int AccessorSetSidePos(lua_State *l);

    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.new(x, y, z)
     * \endcode
     * @param x 
     * @param y 
     * @param z 
     * @return Constructed Vec3i(x, y, z) object
     */
    static Vec3i Vec3i_new(int32 x, int32 y, int32 z);

    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.zero()
     * \endcode
     * @return Constructed Vec3i(0, 0, 0) object
     */
    static Vec3i Vec3i_zero();

    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.one()
     * \endcode
     * @return Constructed Vec3i(1, 1, 1) object
     */
    static Vec3i Vec3i_one();
    
    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.up()
     * \endcode
     * @return Constructed Vec3i(0, 0, 1) object
     */
    static Vec3i Vec3i_up();

    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.down()
     * \endcode
     * @return Constructed Vec3i(0, 0, -1) object
     */
    static Vec3i Vec3i_down();

    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.left()
     * \endcode
     * @return Constructed Vec3i(0, 1, 0) object
     */
    static Vec3i Vec3i_left();

    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.right()
     * \endcode
     * @return Constructed Vec3i(0, -1, 0) object
     */
    static Vec3i Vec3i_right();

    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.back()
     * \endcode
     * @return Constructed Vec3i(-1, 0, 0) object
     */
    static Vec3i Vec3i_back();
    
    /**
     * @brief lua syntax
     * \code{.lua}
     * Vec3i.front()
     * \endcode
     * @return Constructed Vec3i(1, 0, 0) object
     */
    static Vec3i Vec3i_front();

    static int BlockLogicCreateAccessor(lua_State *l);
    static UClass *GetClass(const std::string &name);
};
} // namespace evo