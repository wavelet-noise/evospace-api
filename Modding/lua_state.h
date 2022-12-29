// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/CoordinateSystem.h"
#include "Evospace/Shared/ThirdParty/luabridge.h"
#include "Evospace/Shared/abstract_error.h"

#include <string>

struct lua_State;

namespace evo {

/**
 * @brief Most basic lua state class
 */
class LuaState {
  public:
    static int l_my_print(lua_State *L);

    LuaState();

    /**
     * @brief Find Unreal Engine UClass
     * @details lua syntax
     * @code{.lua}
     * get_class("name")
     * @endcode
     * @param Class name
     * @return Class object
     */
    static UClass *FindClass(std::string_view name);
    static UClass *LoadClass(std::string_view name);
    static UTexture2D *GetTexture(std::string_view name);
    static UMaterialInterface *GetMaterial(std::string_view name);

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
    static Vec3i Vec3i_new(int32 x, int32 y, int32 z) noexcept;

    /**
     * @brief Construct Vec3i from (0, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.zero()
     * @endcode
     * @return Constructed Vec3i(0, 0, 0) object
     */
    static Vec3i Vec3i_zero() noexcept;

    /**
     * @brief Construct Vec3i from (1, 1, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.one()
     * @endcode
     * @return Constructed Vec3i(1, 1, 1) object
     */
    static Vec3i Vec3i_one() noexcept;

    /**
     * @brief Construct Vec3i from up (0, 0, 1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.up()
     * @endcode
     * @return Constructed Vec3i(0, 0, 1) object
     */
    static Vec3i Vec3i_up() noexcept;

    /**
     * @brief Construct Vec3i from (0, 0, -1)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.down()
     * @endcode
     * @return Constructed Vec3i(0, 0, -1) object
     */
    static Vec3i Vec3i_down() noexcept;

    /**
     * @brief Construct Vec3i from (0, 1, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.left()
     * @endcode
     * @return Constructed Vec3i(0, 1, 0) object
     */
    static Vec3i Vec3i_left() noexcept;

    /**
     * @brief Construct Vec3i from (0, -1, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.right()
     * @endcode
     * @return Constructed Vec3i(0, -1, 0) object
     */
    static Vec3i Vec3i_right() noexcept;

    /**
     * @brief Construct Vec3i from (-1, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.back()
     * @endcode
     * @return Constructed Vec3i(-1, 0, 0) object
     */
    static Vec3i Vec3i_back() noexcept;

    /**
     * @brief Construct Vec3i from (1, 0, 0)
     * @details lua syntax
     * @code{.lua}
     * vec = Vec3i.front()
     * @endcode
     * @return Constructed Vec3i(1, 0, 0) object
     */
    static Vec3i Vec3i_front() noexcept;

    void doFile(std::string_view s) { luaL_dofile(L, s.data()); }

    virtual ~LuaState();

    LuaState(const LuaState &) = delete;
    LuaState &operator=(const LuaState &) = delete;

    lua_State *L = nullptr;

    static int ToByteCode_Writer(
        lua_State *L, const void *Ptr, size_t Size, void *UserData
    ) {
        const auto output = static_cast<std::string *>(UserData);
        const auto ptr = static_cast<const uint8_t *>(Ptr);

        output->insert(output->end(), ptr, ptr + Size);
        return 0;
    }

    static auto to_byte_code(std::string_view code) noexcept -> std::string;

    /**
     * @brief
     * @param Code
     * @param CodePath
     * @param NRet
     * @return
     */
    bool RunCode(
        std::string_view Code, std::string_view CodePath = "", int NRet = 0
    ) noexcept;
    bool RunCode(
        std::string_view Code, std::string_view CodePath, int NArg,
        std::function<void(lua_State *L)> push_args, int NRet = 0
    ) noexcept;

    int AppendPath(lua_State *L, std::string_view path) noexcept;
};
} // namespace evo