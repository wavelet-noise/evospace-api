// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Public/MainGameModLoader.h"
#include "ThirdParty/luabridge/luabridge.h"

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

  virtual void Init();

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
  static UClass *FindClass(const std::string &name);
  static UClass *LoadClass(const std::string &name);
  static UTexture2D *FindTexture(const std::string &name);
  static UMaterialInterface *FindMaterial(const std::string &name);

  void AddLuaPath(const FString &path);

  void doFile(std::string_view s) { luaL_dofile(L, s.data()); }

  virtual ~LuaState();

  lua_State *L = nullptr;

  static int ToByteCode_Writer(
    lua_State *L, const void *ptr, size_t size, void *user_data);

  static std::string ToByteCode(std::string_view code, std::string_view path);
  void processLuaErrorOnStack(std::string_view code);

  luabridge::LuaRef ToLuaRefFunction(std::string_view code, std::string_view path);

  bool HandleLuaResult(const luabridge::LuaResult &res) const;

  void HandleLuaErrorOnStack() const;

  /**
     * @brief
     * @param code string with lua code; it will be running in all loaded
     * context in this lua state
     * @param CodePath label in error log for this code fragment execution
     * @return true if there is no errors
     */
  bool RunCode(std::string_view code, std::string_view CodePath = "");
};
} // namespace evo