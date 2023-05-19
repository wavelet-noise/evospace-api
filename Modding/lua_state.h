// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
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

    void Init();

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