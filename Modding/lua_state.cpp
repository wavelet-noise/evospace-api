// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#include "lua_state.h"

#include "Core/block.h"
#include "Core/item.h"
#include "Core/recipe.h"
#include "Core/static_research.h"
#include "Evospace/IcoGenerator.h"
#include "Evospace/MainGameModLoader.h"
#include "Evospace/Shared/static_logger.h"
#include "actor_components.h"
#include "luabridge_extension.h"
#include "math.h"
#include "misc_evospace.h"

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

bool LuaState::run_code(std::string_view code, std::string_view path) {
    std::string path_decorated = std::string("@") + path.data();
    if (luaL_loadbuffer(L, code.data(), code.size(), path_decorated.data())) {
        LOG(ERROR_LL) << "Lua loading error: " << lua_tostring(L, -1);
        return false;
    } else {
        if (lua_pcall(L, 0, LUA_MULTRET, 0)) {
            handle_lua_error();
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
        auto split_error = split(error, ':');
        auto index = std::stoi(split_error[1]);
        auto split_source = split(code, '\n');
        auto in_error = split_source[index - 1];
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

void LuaState::handle_lua_error(ModLoadingContext &context) {
    context.log(ERROR_LL) << "Lua execution error: " << lua_tostring(L, -1);

    context.log(ERROR_LL) << "Call stack:";
    int level = 0;
    lua_Debug debug_info;
    while (lua_getstack(L, level, &debug_info)) {
        lua_getinfo(L, "nSlf", &debug_info);
        context.log(ERROR_LL)
            << "    " << debug_info.short_src << ":" << debug_info.currentline;
        if (debug_info.name != nullptr)
            context.log(ERROR_LL) << " in function " << debug_info.name;
        ++level;
    }
}

void LuaState::handle_lua_error() {
    LOG(ERROR_LL) << "Lua execution error: " << lua_tostring(L, -1);

    LOG(ERROR_LL) << "Call stack:";
    int level = 0;
    lua_Debug debug_info;
    while (lua_getstack(L, level, &debug_info)) {
        lua_getinfo(L, "nSlf", &debug_info);
        LOG(ERROR_LL) << "    " << debug_info.short_src << ":"
                      << debug_info.currentline;
        if (debug_info.name != nullptr)
            LOG(ERROR_LL) << " in function " << debug_info.name;
        ++level;
    }
}

int LuaState::l_my_print(lua_State *L) {
    int nargs = lua_gettop(L);

    for (int i = 1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            LOG(TRACE_LL) << "Lua: " << lua_tostring(L, i);
        } else if (lua_isnumber(L, i)) {
            LOG(TRACE_LL) << "Lua: " << lua_tonumber(L, i);
        } else if (lua_isboolean(L, i)) {
            LOG(TRACE_LL) << "Lua: "
                          << (lua_toboolean(L, i) ? "true" : "false");
        } else if (lua_isnil(L, i)) {
            LOG(TRACE_LL) << "Lua: nil";
        } else if (luabridge::isInstance<UBlock>(L, i)) {
            auto block = luabridge::Stack<UBlock *>::get(L, i);
            LOG(TRACE_LL) << "Lua: UBlock " << block.value()->name;
        } else if (luabridge::isInstance<UItem>(L, i)) {
            auto item = luabridge::Stack<UItem *>::get(L, i);
            LOG(TRACE_LL) << "Lua: UItem " << item.value()->name;
        } else if (luabridge::isInstance<FItemData>(L, i)) {
            auto item = luabridge::Stack<FItemData>::get(L, i);
            LOG(TRACE_LL) << "Lua: ItemData {"
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
            LOG(WARN_LL) << "Lua: print not implemented type";
        }
    }

    return 0;
}

LuaState::LuaState() {
    L = luaL_newstate();

    luaL_openlibs(L);

    luabridge::setGlobal(L, nullptr, "os");
    luabridge::setGlobal(L, nullptr, "coroutine");
    luabridge::setGlobal(L, nullptr, "io");
    luabridge::setGlobal(L, nullptr, "utf8");

    luabridge::setGlobal(L, &LuaState::l_my_print, "print");

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

    LOG(TRACE_LL) << "Lua actor component registering";

    registerComponentClasses(L);

    LOG(TRACE_LL) << "Lua extra math registering";

    registerMathClasses(L);

    LOG(TRACE_LL) << "Lua misc classes registering";

    registerMiscClasses(L);

    run_code(
        "require('jit') if type(jit) == 'table' then print(jit.version) else "
        "print('jit fatal error') end",
        "jit_test"
    );
}

UClass *LuaState::find_class(std::string_view name) {
    auto type = FindObject<UClass>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        LOG(ERROR_LL) << "Class not found " << name;
    } else {
        LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
    }

    return type;
}

UClass *LuaState::load_class(std::string_view name) {
    auto type = LoadObject<UClass>(nullptr, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        LOG(ERROR_LL) << "Class not found " << name;
    } else {
        LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
    }

    return type;
}

UTexture2D *LuaState::find_texture(std::string_view name) {
    auto type = FindObject<UTexture2D>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        LOG(WARN_LL) << "Texture not found " << name;
    } else {
        LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
    }

    return type;
}

UMaterialInterface *LuaState::find_material(std::string_view name) {
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
    // if (L != nullptr) {
    //
    //     lua_close(L);
    //     L = nullptr;
    // }
}
} // namespace evo