// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/CoordinateMinimal.h"
#include "Evospace/Shared/ThirdParty/luabridge.h"
#include "Evospace/Shared/abstract_error.h"

#include <string>

struct lua_State;
class ModLoadingContext;

namespace evo {

/**
 * @brief Most basic lua state class
 */
class LuaState {
  public:
    static int l_my_print(lua_State *L);

    LuaState();

    LuaState(const LuaState &v) = delete;
    LuaState &operator=(const LuaState &v) = delete;

    /**
     * @brief Find Unreal Engine UClass
     * @details lua syntax
     * @code{.lua}
     * get_class("name")
     * @endcode
     * @param Class name
     * @return Class object
     */
    static UClass *find_class(std::string_view name);
    static UClass *load_class(std::string_view name);
    static UTexture2D *find_texture(std::string_view name);
    static UMaterialInterface *find_material(std::string_view name);

    void add_lua_path(const std::string &path);

    /**
     * @brief Construct Vec3i from 3 numbers
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.new(x, y, z)
     * @endcode
     * @param x
     * @param y
     * @param z
     * @return Constructed Vec3i(x, y, z) object
     */
    static Vec3i Vec3i_new(int32 x, int32 y, int32 z);

    /**
     * @brief Construct Vec3i from (0, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.zero()
     * @endcode
     * @return Constructed Vec3i(0, 0, 0) object
     */
    static Vec3i Vec3i_zero();

    /**
     * @brief Construct Vec3i from (1, 1, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.one()
     * @endcode
     * @return Constructed Vec3i(1, 1, 1) object
     */
    static Vec3i Vec3i_one();

    /**
     * @brief Construct Vec3i from up (0, 0, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.up()
     * @endcode
     * @return Constructed Vec3i(0, 0, 1) object
     */
    static Vec3i Vec3i_up();

    /**
     * @brief Construct Vec3i from (0, 0, -1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.down()
     * @endcode
     * @return Constructed Vec3i(0, 0, -1) object
     */
    static Vec3i Vec3i_down();

    /**
     * @brief Construct Vec3i from (0, 1, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.left()
     * @endcode
     * @return Constructed Vec3i(0, 1, 0) object
     */
    static Vec3i Vec3i_left();

    /**
     * @brief Construct Vec3i from (0, -1, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.right()
     * @endcode
     * @return Constructed Vec3i(0, -1, 0) object
     */
    static Vec3i Vec3i_right();

    /**
     * @brief Construct Vec3i from (-1, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.back()
     * @endcode
     * @return Constructed Vec3i(-1, 0, 0) object
     */
    static Vec3i Vec3i_back();

    /**
     * @brief Construct Vec3i from (1, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.front()
     * @endcode
     * @return Constructed Vec3i(1, 0, 0) object
     */
    static Vec3i Vec3i_front();

    void doFile(std::string_view s) { luaL_dofile(L, s.data()); }

    virtual ~LuaState();

    lua_State *L = nullptr;

    static int ToByteCode_Writer(
        lua_State *L, const void *ptr, size_t size, void *user_data
    );

    static auto to_byte_code(std::string_view code, std::string_view path)
        -> std::string;

    void handle_lua_error(ModLoadingContext &context);

    void handle_lua_error();

    /**
     * @brief
     * @param code string with lua code; it will be running in all loaded
     * context in this lua state
     * @param CodePath label in error log for this code fragment execution
     * @return true if there is no errors
     */
    bool run_code(std::string_view code, std::string_view CodePath = "");
};
} // namespace evo