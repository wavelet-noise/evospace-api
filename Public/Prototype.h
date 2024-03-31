// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once

#include "ThirdParty/luabridge/LuaBridge.h"
#include "StaticLogger.h"
#include "Evospace/MainGameOwner.h"

class Base;

/*.addStaticFunction("get", &evo::DB::get<type>)       */ /*.addStaticFunction("get_derived", &evo::DB::get_derived<type>)   */
#define EVO_LUA_CODEGEN_DB(type, name)                                                                                      \
  public:                                                                                                                   \
  static type *lua_codegen_cast(UObject *parent_inst) {                                                                     \
    return Cast<type>(parent_inst);                                                                                         \
  }                                                                                                                         \
  static void lua_reg_internal(lua_State *L) {                                                                              \
    LOG(INFO_LL) << "Registering lua " << #name;                                                                            \
    luabridge::getGlobalNamespace(L)                                                                                        \
      .beginClass<type>(#name)                                                                                              \
      .addStaticFunction(                                                                                                   \
        "find", +[](std::string_view name) { return FindObject<type>(EVO_ASSET_OWNER(), UTF8_TO_TCHAR(name.data())); })     \
      .addStaticFunction("cast", &type::lua_codegen_cast)                                                                   \
      .addStaticFunction(                                                                                                   \
        "new", +[](std::string_view newName) { return NewObject<type>(EVO_ASSET_OWNER(), UTF8_TO_TCHAR(newName.data())); }) \
      .addStaticFunction("get_class", []() { return type::StaticClass(); })                                                 \
      .endClass();                                                                                                          \
  }

/*.addStaticFunction("get", &evo::DB::get<U##type>) */ /*.addStaticFunction("get_derived", &evo::DB::get_derived<U##type>) */
#define EVO_LUA_CODEGEN_DB_EX(type)                                                                                            \
  public:                                                                                                                      \
  static U##type *lua_codegen_cast(UObject *parent_inst) {                                                                     \
    return Cast<U##type>(parent_inst);                                                                                         \
  }                                                                                                                            \
  static void lua_reg_internal(lua_State *L) {                                                                                 \
    LOG(INFO_LL) << "Registering lua " << #type;                                                                               \
    luabridge::getGlobalNamespace(L)                                                                                           \
      .beginClass<U##type>(#type)                                                                                              \
      .addStaticFunction(                                                                                                      \
        "find", +[](std::string_view name) { return FindObject<U##type>(EVO_ASSET_OWNER(), UTF8_TO_TCHAR(name.data())); })     \
      .addStaticFunction("cast", &U##type::lua_codegen_cast)                                                                   \
      .addStaticFunction(                                                                                                      \
        "new", +[](std::string_view newName) { return NewObject<U##type>(EVO_ASSET_OWNER(), UTF8_TO_TCHAR(newName.data())); }) \
      .addStaticFunction("get_class", []() { return U##type::StaticClass(); })                                                 \
      .endClass();                                                                                                             \
  }

/*.addStaticFunction("get", &evo::DB::get<type>)   */ /* .addStaticFunction("get_derived", &evo::DB::get_derived<type>)  */
#define EVO_LUA_CODEGEN_EMPTY(type, parent, name)                                                                           \
  public:                                                                                                                   \
  static void lua_reg(lua_State *L) {                                                                                       \
    LOG(INFO_LL) << "Registering lua " << #name;                                                                            \
    luabridge::getGlobalNamespace(L)                                                                                        \
      .deriveClass<type, parent>(#name)                                                                                     \
      .addStaticFunction(                                                                                                   \
        "find", +[](std::string_view name) { return FindObject<type>(EVO_ASSET_OWNER(), UTF8_TO_TCHAR(name.data())); })     \
      .addStaticFunction("cast", &type::lua_codegen_cast)                                                                   \
      .addStaticFunction(                                                                                                   \
        "new", +[](std::string_view newName) { return NewObject<type>(EVO_ASSET_OWNER(), UTF8_TO_TCHAR(newName.data())); }) \
      .addStaticFunction("get_class", []() { return type::StaticClass(); })                                                 \
      .endClass();                                                                                                          \
  }