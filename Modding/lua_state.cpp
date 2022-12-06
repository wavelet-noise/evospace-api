#include "lua_state.h"

#include "Evospace/Shared/static_logger.h"

namespace evo {
bool LuaState::RunCode(
    std::string_view Code, std::string_view CodePath, int NRet
) noexcept {
    if (luaL_loadbuffer(L, Code.data(), Code.size(), CodePath.data())) {
        StaticLogger::Get().Log(
            "Lua loading error: " + std::string(lua_tostring(L, -1))
        );
        return false;
    } else {
        if (lua_pcall(L, 0, NRet, 0)) {
            StaticLogger::Get().Log(
                "Lua execution error: " + std::string(lua_tostring(L, -1))
            );
            return false;
        }
    }

    return true;
}

std::vector<std::string> split(std::string_view s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s.data());
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

auto LuaState::to_byte_code(
    std::string_view code, std::string_view context
) noexcept -> result<std::string, std::unique_ptr<AbstractError>> {
    const char *CodeRaw = code.data();
    std::string Output;

    lua_State *L = luaL_newstate();
    if (auto err = luaL_loadbuffer(L, CodeRaw, code.length(), "@string")) {
        std::string error = lua_tostring(L, -1);
        lua_close(L);
        auto splited_error = split(error, ':');
        auto index = std::stoi(splited_error[1]);
        auto splitted_source = split(code, '\n');
        auto in_error = splitted_source[index - 1];
        return failure(
            std::make_unique<LuaStateBufferLoadError>(error, in_error)
        );
    }

    if (lua_dump(L, ToByteCode_Writer, &Output, 1)) {
        auto error = lua_tostring(L, -1);
        lua_close(L);
        return failure(std::make_unique<LuaStateCodeDumpError>(error));
    }

    lua_close(L);
    return Output;
}

int LuaState::l_my_print(lua_State *L) {
    int nargs = lua_gettop(L);

    for (int i = 1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            std::cout << "Lua print: " << lua_tostring(L, i) << std::endl;
        } else if (lua_isnumber(L, i)) {
            std::cout << "Lua print: " << lua_tonumber(L, i) << std::endl;
        } else if (lua_isboolean(L, i)) {
            std::cout << "Lua print: " << lua_toboolean(L, i) << std::endl;
        } else if (luabridge::Stack<FVector2D>::isInstance(L, i)) {
            auto vec = luabridge::Stack<FVector2D>::get(L, i);
            std::cout << "Lua print: vec2{" << vec.X << ", " << vec.Y << "}"
                      << std::endl;
        }
        // else if (Stack<FVector2D>::isInstance(L, i)) {
        // 	auto vec = Stack<glm::ivec2>::get(L, i);
        // 	std::cout << "lua print: ivec2{" << vec.x << ", " << vec.y <<
        // "}" << std::endl;
        // }
        else {
            std::cout << "Lua print: not implementer type" << std::endl;
        }
    }

    return 0;
}

LuaState::LuaState() {
    L = luaL_newstate();

    luaL_requiref(L, "package", luaopen_package, 1);
    lua_pop(L, 1);

    {
        luaL_requiref(L, "_G", luaopen_base, 1);
        lua_pop(L, 1);
    }

    //{
    //	luaL_requiref(L, "coroutine", luaopen_coroutine, 1);
    //	lua_pop(L, 1);
    //}

    {
        luaL_requiref(L, "table", luaopen_table, 1);
        lua_pop(L, 1);
    }

    //{
    //	luaL_requiref(L, "io", luaopen_io, 1);
    //	lua_pop(L, 1);
    //}

    //{
    //	luaL_requiref(L, "os", luaopen_os, 1);
    //	lua_pop(L, 1);
    //}

    {
        luaL_requiref(L, "string", luaopen_string, 1);
        lua_pop(L, 1);
    }

    {
        luaL_requiref(L, "math", luaopen_math, 1);
        lua_pop(L, 1);
    }

    {
        luaL_requiref(L, "utf8", luaopen_utf8, 1);
        lua_pop(L, 1);
    }

    {
        luaL_requiref(L, "debug", luaopen_debug, 1);
        lua_pop(L, 1);
    }

    constexpr luaL_Reg print_lib[] = {
        {"print", l_my_print}, {nullptr, nullptr}};

    lua_getglobal(L, "_G");
    luaL_setfuncs(L, print_lib, 0);
    lua_pop(L, 1);

    auto col = luabridge::getGlobal(L, "collectgarbage");
    col("setpause", 100);

    // std::error_code er;
    // const auto ref = luabridge::Stack<luabridge::LuaRef>::get(L, 2);
    //
    // lua_getglobal(L, "string");
    // lua_getfield(L, -1, "dump");
    // lua_remove(L, -2);
    // luabridge::push(L, ref, er);
    //
    // if (er) {
    //     StaticLogger::Get().Log("Dump error: " + er.message());
    //     return;
    // }
    //
    // if (lua_pcall(L, 1, 1, 0)) {
    //     const std::string err = lua_tostring(L, -1);
    //     std::cout << "Error: " << err << std::endl;
    //
    //     lua_getglobal(L, "debug");
    //     lua_getfield(L, -1, "traceback");
    //
    //     if (lua_pcall(L, 0, 1, 0)) {
    //         const std::string err1 = lua_tostring(L, -1);
    //         StaticLogger::Get().Log("Error in debug.traceback() call: " +
    //         err1); return;
    //     }
    //
    //     const std::string stackTrace = lua_tostring(L, -1);
    //     StaticLogger::Get().Log("C++ stack traceback: " + stackTrace);
    //     return;
    // }
    //
    // lua_pop(L, 1);

    using namespace luabridge;

    getGlobalNamespace(L)
    .beginClass<Vec3i>("Vec3i")
    .addStaticFunction("new", &LuaState::Vec3i_new)
    .addStaticFunction("zero", &LuaState::Vec3i_zero)
    .addStaticFunction("up", &LuaState::Vec3i_up)
    .addStaticFunction("down", &LuaState::Vec3i_down)
    .addStaticFunction("left", &LuaState::Vec3i_left)
    .addStaticFunction("right", &LuaState::Vec3i_right)
    .addStaticFunction("back", &LuaState::Vec3i_back)
    .addStaticFunction("front", &LuaState::Vec3i_front)
    .endClass();

    getGlobalNamespace(L).addFunction("get_class", &LuaState::GetClass);
}

UClass *LuaState::GetClass(std::string_view name) {
    using namespace std::string_literals;
    auto type = FindObject<UClass>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        StaticLogger::Get().Log("Class not found " + name);
    }

    return type;
}

LuaState::~LuaState() {
    if (L != nullptr) {
        lua_close(L);
        L = nullptr;
    }
}

Vec3i LuaState::Vec3i_new(int32 x, int32 y, int32 z) {
    return Vec3i(x, y, z);
}

Vec3i LuaState::Vec3i_zero() {
    return Vec3i(0, 0, 0);
}

Vec3i LuaState::Vec3i_one() {
    return Vec3i(1, 1, 1);
}

Vec3i LuaState::Vec3i_left() {
    return Side::Left;
}

Vec3i LuaState::Vec3i_right() {
    return Side::Right;
}

Vec3i LuaState::Vec3i_up() {
    return Side::Up;
}

Vec3i LuaState::Vec3i_down() {
    return Side::Down;
}

Vec3i LuaState::Vec3i_front() {
    return Side::Front;
}

Vec3i LuaState::Vec3i_back() {
    return Side::Back;
}

} // namespace evo