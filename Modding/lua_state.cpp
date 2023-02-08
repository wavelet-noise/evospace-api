// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#include "lua_state.h"

#include "Core/block.h"
#include "Core/item.h"
#include "Core/recipe.h"
#include "Core/static_research.h"
#include "Evospace/IcoGenerator.h"
#include "Evospace/MainGameModLoader.h"
#include "Evospace/Shared/static_logger.h"

namespace evo {

void LuaState::add_lua_path(const std::string &path) {
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "path");
    std::string cur_path = lua_tostring(L, -1);
    cur_path = cur_path + ";" + path + "/?.lua";
    lua_pop(L, 1);
    lua_pushstring(L, cur_path.data());
    lua_setfield(L, -2, "path");
    lua_pop(L, 1);
}

bool LuaState::RunCode(std::string_view code, std::string_view path, int NRet) {
    std::string path_decorated = std::string("@") + path.data();
    if (luaL_loadbuffer(L, code.data(), code.size(), path_decorated.data())) {
        LOG(ERROR_LL) << "Lua loading error: " << lua_tostring(L, -1);
        return false;
    } else {
        if (lua_pcall(L, 0, NRet, 0)) {
            LOG(ERROR_LL) << "Lua execution error: " << lua_tostring(L, -1);

            LOG(ERROR_LL) << "Call stack:";
            int level = 0;
            lua_Debug debug_info;
            while (lua_getstack(L, level, &debug_info)) {
                lua_getinfo(L, "nSlf", &debug_info);
                std::cerr << "    " << debug_info.short_src << ":"
                          << debug_info.currentline;
                if (debug_info.name != nullptr)
                    LOG(ERROR_LL) << " in function " << debug_info.name;
                ++level;
            }

            return false;
        }
    }

    return true;
}

bool LuaState::RunCode(
    AsyncMessageObject &msg, std::string_view code, std::string_view path,
    int NRet
) {
    std::string path_decorated = std::string("@") + path.data();
    if (luaL_loadbuffer(L, code.data(), code.size(), path_decorated.data())) {
        msg.Log(ERROR_LL) << "Lua loading error: " << lua_tostring(L, -1);
        return false;
    } else {
        if (lua_pcall(L, 0, NRet, 0)) {
            msg.Log(ERROR_LL) << "Lua execution error: " << lua_tostring(L, -1);

            msg.Log(ERROR_LL) << "Call stack:";
            int level = 0;
            lua_Debug debug_info;
            while (lua_getstack(L, level, &debug_info)) {
                lua_getinfo(L, "nSlf", &debug_info);
                std::cerr << "    " << debug_info.short_src << ":"
                          << debug_info.currentline;
                if (debug_info.name != nullptr)
                    msg.Log(ERROR_LL) << " in function " << debug_info.name;
                ++level;
            }

            return false;
        }
    }

    return true;
}

bool LuaState::RunCode(
    std::string_view code, std::string_view path, int NArg,
    std::function<void(lua_State *L)> push_args, int NRet
) {
    std::string path_decorated = std::string("@") + path.data();
    if (luaL_loadbuffer(L, code.data(), code.size(), path_decorated.data())) {
        LOG(ERROR_LL) << "Lua loading error: " << lua_tostring(L, -1);
        return false;
    } else {
        push_args(L);
        if (lua_pcall(L, NArg, NRet, 0)) {
            LOG(ERROR_LL) << "Lua execution error: " << lua_tostring(L, -1);

            LOG(ERROR_LL) << "Call stack:" << std::endl;
            int level = 0;
            lua_Debug debug_info;
            while (lua_getstack(L, level, &debug_info)) {
                lua_getinfo(L, "nSlf", &debug_info);
                std::cerr << "    " << debug_info.short_src << ":"
                          << debug_info.currentline;
                if (debug_info.name != nullptr)
                    LOG(ERROR_LL) << " in function " << debug_info.name;
                ++level;
            }

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

int LuaState::ToByteCode_Writer(
    lua_State *L, const void *ptr, size_t size, void *user_data
) {
    const auto output = static_cast<std::string *>(user_data);
    const auto ptr_u8 = static_cast<const uint8_t *>(ptr);

    output->insert(output->end(), ptr_u8, ptr_u8 + size);
    return 0;
}
auto LuaState::to_byte_code(std::string_view code, std::string_view path)
    -> std::string {
    std::string output;
    std::string path_decorated = std::string("@") + path.data();
    lua_State *L = luaL_newstate();
    if (auto err = luaL_loadbuffer(
            L, code.data(), code.length(), path_decorated.data()
        )) {
        std::string error = lua_tostring(L, -1);
        lua_close(L);
        auto splited_error = split(error, ':');
        auto index = std::stoi(splited_error[1]);
        auto splitted_source = split(code, '\n');
        auto in_error = splitted_source[index - 1];
        LOG(ERROR_LL) << "Load buffer error: " << error << "; line " << index
                      << ": " << in_error;
        return "";
    }

    if (lua_dump(L, ToByteCode_Writer, &output)) {
        auto error = lua_tostring(L, -1);
        lua_close(L);
        LOG(ERROR_LL) << "Dump error: " << error;
        return "";
    }

    lua_close(L);
    return output;
}

int LuaState::l_my_print(lua_State *L) {
    int nargs = lua_gettop(L);

    for (int i = 1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            LOG(TRACE_LL) << "Lua print: " << lua_tostring(L, i);
        } else if (lua_isnumber(L, i)) {
            LOG(TRACE_LL) << "Lua print: " << lua_tonumber(L, i);
        } else if (lua_isboolean(L, i)) {
            LOG(TRACE_LL) << "Lua print: "
                          << (lua_toboolean(L, i) ? "true" : "false");
        } else if (lua_isnil(L, i)) {
            LOG(TRACE_LL) << "Lua print: nil";
        } else if (luabridge::isInstance<UBlock>(L, i)) {
            auto block = luabridge::Stack<UBlock *>::get(L, i);
            LOG(TRACE_LL) << "Lua print: UBlock " << block.value()->name;
        } else if (luabridge::isInstance<UItem>(L, i)) {
            auto item = luabridge::Stack<UItem *>::get(L, i);
            LOG(TRACE_LL) << "Lua print: UItem " << item.value()->name;
        } else if (luabridge::isInstance<FItemData>(L, i)) {
            auto item = luabridge::Stack<FItemData>::get(L, i);
            LOG(TRACE_LL) << "Lua print: ItemData {"
                          << (item.value().item ? item.value().item->name
                                                : "nullptr")
                          << ", " << item.value().count << "}";
        }
        // else if (Stack<FVector2D>::isInstance(L, i)) {
        // 	auto vec = Stack<glm::ivec2>::get(L, i);
        // 	std::cout << "lua print: ivec2{" << vec.x << ", " << vec.y <<
        // "}" << std::endl;
        // }
        // if (luabridge::Stack<UPrototype *>::isInstance(L, i)) {
        //     auto stat = luabridge::Stack<UPrototype *>::get(L, i);
        //     LOG(TRACE_LL) << "Lua print: "
        //               << TCHAR_TO_UTF8(*stat->GetClass()->GetName()) << ""
        //               << stat->name;
        // }
        else {
            LOG(WARN_LL) << "Lua print: print not implemented type";
        }
    }

    return 0;
}

LuaState::LuaState() {
    L = luaL_newstate();

    luaL_openlibs(L);

    // luaL_requiref(L, "package", luaopen_package, 1);
    // lua_pop(L, 1);

    // {
    //     luaL_requiref(L, "_G", luaopen_base, 1);
    //     lua_pop(L, 1);
    // }
    //
    // //{
    // //	luaL_requiref(L, "coroutine", luaopen_coroutine, 1);
    // //	lua_pop(L, 1);
    // //}
    //
    // {
    //     luaL_requiref(L, "table", luaopen_table, 1);
    //     lua_pop(L, 1);
    // }
    //
    // //{
    // //	luaL_requiref(L, "io", luaopen_io, 1);
    // //	lua_pop(L, 1);
    // //}
    //
    // //{
    // //	luaL_requiref(L, "os", luaopen_os, 1);
    // //	lua_pop(L, 1);
    // //}
    //
    // {
    //     luaL_requiref(L, "string", luaopen_string, 1);
    //     lua_pop(L, 1);
    // }
    //
    // {
    //     luaL_requiref(L, "math", luaopen_math, 1);
    //     lua_pop(L, 1);
    // }
    //
    // // {
    // //     luaL_requiref(L, "utf8", luaopen_utf8, 1);
    // //     lua_pop(L, 1);
    // // }
    //
    // {
    //     luaL_requiref(L, "debug", luaopen_debug, 1);
    //     lua_pop(L, 1);
    // }

    luabridge::getGlobalNamespace(L).addFunction(
        "print", &LuaState::l_my_print
    );

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

    LOG(TRACE_LL) << "Lua state initialized";

    auto ver = luabridge::getGlobal(L, "_VERSION");
    LOG(TRACE_LL) << ver.tostring();

    using namespace luabridge;

    getGlobalNamespace(L)
        .beginClass<UIcoGenerator>("IcoGenerator")
        .addStaticFunction("combine", &UIcoGenerator::combine)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UTexture2D>("Texture")
        .addStaticFunction("find", &LuaState::GetTexture)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UMaterialInterface>("Material")
        .addStaticFunction("load", &LuaState::GetMaterial)
        .endClass();

    getGlobalNamespace(L).beginClass<UStaticMesh>("Mesh").endClass();

    getGlobalNamespace(L).beginClass<UObject>("Object").endClass();

    getGlobalNamespace(L)
        .beginClass<UClass>("Class")
        .addStaticFunction("find", &LuaState::FindClass)
        .addStaticFunction("load", &LuaState::LoadClass)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<APlayerController>("PlayerController")
        .endClass();

    getGlobalNamespace(L)
        .beginClass<Vec3i>("Vec3i")
        .addStaticFunction("new", &LuaState::Vec3i_new)
        .addStaticProperty("zero", &LuaState::Vec3i_zero)
        .addStaticProperty("up", &LuaState::Vec3i_up)
        .addStaticProperty("down", &LuaState::Vec3i_down)
        .addStaticProperty("left", &LuaState::Vec3i_left)
        .addStaticProperty("right", &LuaState::Vec3i_right)
        .addStaticProperty("back", &LuaState::Vec3i_back)
        .addStaticProperty("front", &LuaState::Vec3i_front)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<KeyTable>("Loc")
        .addStaticFunction("new", &KeyTable::create)
        .addStaticFunction("new_param", &KeyTable::create_param)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<FItemData>("ItemData")
        .addStaticFunction(
            "new", +[]() { return FItemData(); }
        )
        .addProperty("count", &FItemData::count)
        .addProperty("item", &FItemData::item)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<URecipe>("Recipe")
        .addStaticFunction("new", &URecipe::lua_new)
        .addProperty("loss", &URecipe::loss)
        .addProperty("ticks", &URecipe::ticks)
        .addProperty("input", &URecipe::input, false)
        .addProperty("output", &URecipe::output, false)
        .addProperty("res_input", &URecipe::res_input)
        .addProperty("res_output", &URecipe::res_output)
        .addProperty("name", &URecipe::get_name, &URecipe::set_name)
        .endClass();

    RunCode(
        "require('jit') if type(jit) == 'table' then print(jit.version) else "
        "print('jit fatal error') end",
        "jit_test",
        0
    );
}

int LuaState::AppendPath(lua_State *L, std::string_view path) {
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "path");
    std::string npath = path.data();
    npath.append(";");
    npath.append(lua_tostring(L, -1));
    lua_pop(L, 1);
    lua_pushstring(L, npath.c_str());
    lua_setfield(L, -2, "path");
    lua_pop(L, 1);
    return 0;
}

UClass *LuaState::FindClass(std::string_view name) {
    auto type = FindObject<UClass>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        LOG(ERROR_LL) << "Class not found " << name;
    } else {
        LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
    }

    return type;
}

UClass *LuaState::LoadClass(std::string_view name) {
    auto type = LoadObject<UClass>(nullptr, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        LOG(ERROR_LL) << "Class not found " << name;
    } else {
        LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
    }

    return type;
}

UTexture2D *LuaState::GetTexture(std::string_view name) {
    auto type = FindObject<UTexture2D>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        LOG(ERROR_LL) << "Texture not found " << name;
    } else {
        LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
    }

    return type;
}

UMaterialInterface *LuaState::GetMaterial(std::string_view name) {
    auto type = LoadObject<UMaterialInterface>(
        nullptr, *(FString(TEXT("/Game/")) + UTF8_TO_TCHAR(name.data()))
    );

    if (type == nullptr) {
        LOG(ERROR_LL) << "Material not found " << name;
    } else {
        LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
    }

    return type;
}

LuaState::~LuaState() {
    if (L != nullptr) {
        lua_close(L);
        L = nullptr;
    }
}

Vec3i LuaState::Vec3i_new(int32 x, int32 y, int32 z) { return Vec3i(x, y, z); }

Vec3i LuaState::Vec3i_zero() { return Vec3i(0, 0, 0); }

Vec3i LuaState::Vec3i_one() { return Vec3i(1, 1, 1); }

Vec3i LuaState::Vec3i_left() { return Side::Left; }

Vec3i LuaState::Vec3i_right() { return Side::Right; }

Vec3i LuaState::Vec3i_up() { return Side::Up; }

Vec3i LuaState::Vec3i_down() { return Side::Down; }

Vec3i LuaState::Vec3i_front() { return Side::Front; }

Vec3i LuaState::Vec3i_back() { return Side::Back; }

} // namespace evo