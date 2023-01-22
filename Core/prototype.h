// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once

#include "../static_logger.h"
#include "database.h"

#include "prototype.generated.h"

class Base;

/*namespace Events {
        struct OnAnimationFinished
        {
                ECS_DECLARE_TYPE;

                Entity* entity;
                ComponentHandle<Render> render;
        };

        struct OnEntitySpawned
        {
                ECS_DECLARE_TYPE;

                Entity* entity;
        };
}*/

#define EVO_LUA_CODEGEN_DB(type, name)                                         \
  public:                                                                      \
    static type *lua_codegen_cast(UPrototype *parent_inst) {                   \
        return Cast<type>(parent_inst);                                        \
    }                                                                          \
    static void RegisterCommonLua(lua_State *L) {                              \
        LOG(TRACE_LL) << "Registering lua " << #name; \
        luabridge::getGlobalNamespace(L)                                       \
            .beginClass<type>(#name)                                           \
            .addStaticFunction("find", &evo::DB::find_mut<type>)               \
            .addStaticFunction("get", &evo::DB::get<type>)                     \
            .addStaticFunction("get_derived", &evo::DB::get_derived<type>)     \
            .addStaticFunction("cast", &type::lua_codegen_cast)                \
            .endClass();                                                       \
    }

#define EVO_LUA_CODEGEN_DB_EX(type)                                            \
  public:                                                                      \
    static U##type *lua_codegen_cast(UPrototype *parent_inst) {                \
        return Cast<U##type>(parent_inst);                                     \
    }                                                                          \
    static void RegisterCommonLua(lua_State *L) {                              \
        LOG(TRACE_LL) << "Registering lua " << #type; \
        luabridge::getGlobalNamespace(L)                                       \
            .beginClass<U##type>(#type)                                        \
            .addStaticFunction("find", &evo::DB::find_mut<U##type>)            \
            .addStaticFunction("get", &evo::DB::get<U##type>)                  \
            .addStaticFunction("get_derived", &evo::DB::get_derived<U##type>)  \
            .addStaticFunction("cast", &U##type::lua_codegen_cast)             \
            .endClass();                                                       \
    }

#define EVO_LUA_CODEGEN_EMPTY(type, parent, name)                              \
  public:                                                                      \
    static void RegisterLua(lua_State *L) {                                    \
        LOG(TRACE_LL) << "Registering lua " << #name; \
        luabridge::getGlobalNamespace(L)                                       \
            .deriveClass<type, parent>(#name)                                  \
            .addStaticProperty(                                                \
                "class_name", +[]() { return #type; }                          \
            )                                                                  \
            .endClass();                                                       \
    }

UCLASS(Abstract)
/**
 * @brief Super class for all objects stored in database
 */
class UPrototype
    : public UObject { // : public std::enable_shared_from_this<Static> {
    GENERATED_BODY()

  public:
    // Static(const Static &) = delete;
    // Static &operator=(const Static &) = delete;

    /**
     * @brief Object name in database
     */
    std::string name;

  public:
    EVO_LUA_CODEGEN_DB_EX(Prototype);
    static void RegisterLua(lua_State *L);
};