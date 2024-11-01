// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#include "LuaState.h"

#include "StaticLogger.h"
#include "LuaRegistration/ActorComponents.h"
#include "LuaRegistration/Math.h"
#include "LuaRegistration/MiscEvospace.h"
#include "LuaRegistration/ModApi.h"

namespace evo {

void LuaState::AddLuaPath(const FString &path) {
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "path");
  FString cur_path = UTF8_TO_TCHAR(lua_tostring(L, -1));
  cur_path = cur_path + ";" + path + "/?.lua";
  lua_pop(L, 1);
  lua_pushstring(L, TCHAR_TO_UTF8(*cur_path));
  lua_setfield(L, -2, "path");
  lua_pop(L, 1);
}

bool LuaState::RunCode(std::string_view code, std::string_view path) {
  std::string path_decorated = std::string("@") + path.data();
  if (luaL_loadbuffer(L, code.data(), code.size(), path_decorated.data())) {
    LOG(ERROR_LL) << "Lua loading error: " << UTF8_TO_TCHAR(lua_tostring(L, -1));
    return false;
  }

  if (lua_pcall(L, 0, LUA_MULTRET, 0)) {
    HandleLuaErrorOnStack();
    return false;
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
  lua_State *L, const void *ptr, size_t size, void *user_data) {
  const auto output = static_cast<std::string *>(user_data);
  const auto ptr_u8 = static_cast<const uint8_t *>(ptr);

  output->insert(output->end(), ptr_u8, ptr_u8 + size);
  return 0;
}

std::string LuaState::ToByteCode(std::string_view code, std::string_view path) {
  std::string output;
  std::string path_decorated = std::string("@") + path.data();
  lua_State *L = luaL_newstate();
  if (auto err = luaL_loadbuffer(
        L, code.data(), code.length(), path_decorated.data())) {
    std::string error = lua_tostring(L, -1);
    lua_close(L);
    auto split_error = split(error, ':');
    auto index = std::stoi(split_error[1]);
    auto split_source = split(code, '\n');
    auto in_error = split_source[index - 1];
    LOG(ERROR_LL) << "Load buffer error: " << UTF8_TO_TCHAR(error.data()) << "; line " << index
                  << ": " << UTF8_TO_TCHAR(in_error.data());
    return "";
  }

  if (lua_dump(L, ToByteCode_Writer, &output)) {
    auto error = lua_tostring(L, -1);
    lua_close(L);
    LOG(ERROR_LL) << "Dump error: " << UTF8_TO_TCHAR(error);
    return "";
  }

  lua_close(L);
  return output;
}

void LuaState::processLuaErrorOnStack(std::string_view code) {
  std::string error = lua_tostring(L, -1);
  auto split_error = split(error, ':');
  auto index = std::stoi(split_error[1]);
  auto split_source = split(code, '\n');
  auto in_error = split_source[index - 1];
  LOG(ERROR_LL) << "Load buffer error: " << UTF8_TO_TCHAR(error.data()) << "; line " << index
                << ": " << UTF8_TO_TCHAR(in_error.data());
  lua_pop(L, 1);
}

luabridge::LuaRef LuaState::ToLuaRefFunction(std::string_view code, std::string_view path) {
  std::string output;
  std::string path_decorated = std::string("@") + path.data();
  if (auto err = luaL_loadbuffer(L, code.data(), code.length(), path_decorated.data())) {
    processLuaErrorOnStack(code);
    return luabridge::LuaRef(L, nullptr);
  }

  luabridge::LuaRef funcRef = luabridge::LuaRef::fromStack(L, -1);
  lua_pop(L, 1);

  return funcRef;
}

bool LuaState::HandleLuaResult(const luabridge::LuaResult &res) const {
  if (res.wasOk())
    return true;

  LOG(ERROR_LL) << "Lua result error: " << UTF8_TO_TCHAR(res.errorMessage().data());

  LOG(ERROR_LL) << "Call stack:";
  int level = 0;
  lua_Debug debug_info;
  while (lua_getstack(L, level, &debug_info)) {
    lua_getinfo(L, "nSlf", &debug_info);
    LOG(ERROR_LL) << "    " << UTF8_TO_TCHAR(debug_info.short_src) << ":"
                  << debug_info.currentline;
    if (debug_info.name != nullptr)
      LOG(ERROR_LL) << " in function " << UTF8_TO_TCHAR(debug_info.name);
    ++level;
  }

  return false;
}

void LuaState::HandleLuaErrorOnStack() const {
  LOG(ERROR_LL) << "Lua execution error: " << UTF8_TO_TCHAR(lua_tostring(L, -1));

  LOG(ERROR_LL) << "Call stack:";
  int level = 0;
  lua_Debug debug_info;
  while (lua_getstack(L, level, &debug_info)) {
    lua_getinfo(L, "nSlf", &debug_info);
    LOG(ERROR_LL) << "    " << UTF8_TO_TCHAR(debug_info.short_src) << ":"
                  << debug_info.currentline;
    if (debug_info.name != nullptr)
      LOG(ERROR_LL) << " in function " << UTF8_TO_TCHAR(debug_info.name);
    ++level;
  }
}

int LuaState::l_my_print(lua_State *L) {
  int nargs = lua_gettop(L);

  for (int i = 1; i <= nargs; i++) {
    if (lua_isstring(L, i)) {
      LOG(INFO_LL) << "Lua: " << UTF8_TO_TCHAR(lua_tostring(L, i));
    } else if (lua_isnumber(L, i)) {
      LOG(INFO_LL) << "Lua: " << lua_tonumber(L, i);
    } else if (lua_isboolean(L, i)) {
      LOG(INFO_LL) << "Lua: " << lua_toboolean(L, i);
    } else if (lua_isnil(L, i)) {
      LOG(INFO_LL) << "Lua: nil";
    } else {
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

  LOG(INFO_LL) << "Lua state is constructed";
}

void LuaState::Init() {

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

  LOG(INFO_LL) << "Lua actor component registering";

  registerComponentClasses(L);

  LOG(INFO_LL) << "Lua extra math registering";

  registerMathClasses(L);

  LOG(INFO_LL) << "Lua misc classes registering";

  registerMiscClasses(L);

  LOG(INFO_LL) << "Lua state initialized";

  auto ver = luabridge::getGlobal(L, "_VERSION");
  LOG(INFO_LL) << UTF8_TO_TCHAR(ver.tostring().data());

  RunCode(
    "require('jit') if type(jit) == 'table' then print(jit.version) else "
    "print('jit fatal error') end",
    "jit_test");
}

UClass *LuaState::FindClass(const std::string &name) {
  auto type = FindObject<UClass>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

  if (type == nullptr) {
    LOG(ERROR_LL) << "Class not found " << UTF8_TO_TCHAR(name.data());
  } else {
    //LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
  }

  return type;
}

UClass *LuaState::LoadClass(const std::string &name) {
  auto type = LoadObject<UClass>(nullptr, UTF8_TO_TCHAR(name.data()));

  if (type == nullptr) {
    LOG(ERROR_LL) << "Class not loaded " << UTF8_TO_TCHAR(name.data());
  } else {
    //LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
  }

  return type;
}

UTexture2D *LuaState::FindTexture(const std::string &name) {
  auto type = FindObject<UTexture2D>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

  if (type == nullptr) {
    LOG(WARN_LL) << "Texture not found " << UTF8_TO_TCHAR(name.data());
  } else {
    //LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
  }

  return type;
}

UMaterialInterface *LuaState::FindMaterial(const std::string &name) {
  auto type = LoadObject<UMaterialInterface>(nullptr, UTF8_TO_TCHAR(name.data()));

  if (type == nullptr) {
    LOG(ERROR_LL) << "Material not found " << UTF8_TO_TCHAR(name.data());
  } else {
    //LOG(TRACE_LL) << TCHAR_TO_UTF8(*type->GetName()) << " is loaded";
  }

  return type;
}

LuaState::~LuaState() {
  if (L != nullptr) {

    lua_close(L);
    L = nullptr;
  }
}
} // namespace evo