// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/CoordinateMinimal.h"
#include "ThirdParty/luabridge/luabridge.h"

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
     * @brief Static function. Construct Vec3 from 3 numbers
     * @details lua syntax
     * @code{.lua}
     * vec = Vec.new(x, y, z)
     * @endcode
     * @param x
     * @param y
     * @param z
     * @return Vec3(x, y, z) object
     */
    FVector Vec_new(float x, float y, float z);

    /**
     * @brief Static function. Construct Vec2i from 2 numbers
     * @details lua syntax
     * @code{.lua}
     * vec = Vec2i.new(x, y)
     * @endcode
     * @param x
     * @param y
     * @return Constructed Vec3i(x, y) object
     */
    static Vec2i Vec2i_new(int32 x, int32 y);

    /**
     * @brief Static property. Construct Vec2i from (0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec2i.zero()
     * @endcode
     * @return Constructed Vec2i(0, 0) object
     */
    static Vec2i Vec2i_zero();

    /**
     * @brief Static property. Construct Vec3i from (1, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec2i.one()
     * @endcode
     * @return Constructed Vec2i(1, 1) object
     */
    static Vec2i Vec2i_one();

    /**
     * @brief Static function. Construct Vec3i from 3 numbers
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
     * @brief Static property. Construct Vec3i from (0, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.zero()
     * @endcode
     * @return Constructed Vec3i(0, 0, 0) object
     */
    static Vec3i Vec3i_zero();

    /**
     * @brief Static property. Construct Vec3i from (1, 1, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.one()
     * @endcode
     * @return Constructed Vec3i(1, 1, 1) object
     */
    static Vec3i Vec3i_one();

    /**
     * @brief Static property. Construct Vec3i from up (0, 0, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.up()
     * @endcode
     * @return Constructed Vec3i(0, 0, 1) object
     */
    static Vec3i Vec3i_up();

    /**
     * @brief Static property. Construct Vec3i from (0, 0, -1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.down()
     * @endcode
     * @return Constructed Vec3i(0, 0, -1) object
     */
    static Vec3i Vec3i_down();

    /**
     * @brief Static property. Construct Vec3i from (0, 1, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.left()
     * @endcode
     * @return Constructed Vec3i(0, 1, 0) object
     */
    static Vec3i Vec3i_left();

    /**
     * @brief Static property. Construct Vec3i from (0, -1, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.right()
     * @endcode
     * @return Constructed Vec3i(0, -1, 0) object
     */
    static Vec3i Vec3i_right();

    /**
     * @brief Static property. Construct Vec3i from (-1, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.back()
     * @endcode
     * @return Constructed Vec3i(-1, 0, 0) object
     */
    static Vec3i Vec3i_back();

    /**
     * @brief Static function. Construct Vec3i from (1, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.front()
     * @endcode
     * @return Constructed Vec3i(1, 0, 0) object
     */
    static Vec3i Vec3i_front();

    /**
     * @brief Static function. Convert block position to sector position
     * @details lua syntax
     * @code{.lua}
     * vec = cs.bp2sp()
     * @endcode
     * @param bpos Vec3i block position
     * @return Vec3i sector position
     */
    Vec3i cs_bp2sp(const Vec3i &bpos);

    /**
     * @brief Static function. Convert world position to sector position
     * @details lua syntax
     * @code{.lua}
     * vec = cs.cs_w2bp()
     * @endcode
     * @param bpos Vec3 world position
     * @return Vec3i block position
     */
    Vec3i cs_w2bp(const FVector &world);

    /**
     * @brief Static function. Convert block position to world position
     * @details lua syntax
     * @code{.lua}
     * vec = cs.cs_bp2w()
     * @endcode
     * @param bpos Vec3i block position
     * @return Vec3 world position
     */
    FVector cs_bp2w(const Vec3i &bpos);

    /**
     * @brief Static function. Convert world position to sector position
     * @details lua syntax
     * @code{.lua}
     * vec = cs.cs_w2sp()
     * @endcode
     * @param bpos Vec3i world position
     * @return Vec3i sector position
     */
    Vec3i cs_w2sp(const FVector &world);

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