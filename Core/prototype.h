// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
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
    static void lua_reg_internal(lua_State *L) {                               \
        LOG(TRACE_LL) << "Registering lua " << #name;                          \
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
    static void lua_reg_internal(lua_State *L) {                               \
        LOG(TRACE_LL) << "Registering lua " << #type;                          \
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
    static void lua_reg(lua_State *L) {                                    \
        LOG(TRACE_LL) << "Registering lua " << #name;                          \
        luabridge::getGlobalNamespace(L)                                       \
            .deriveClass<type, parent>(#name)                                  \
            .addStaticFunction("find", &evo::DB::find_mut<type>)               \
            .addStaticFunction("get", &evo::DB::get<type>)                     \
            .addStaticFunction("get_derived", &evo::DB::get_derived<type>)     \
            .addStaticFunction("cast", &type::lua_codegen_cast)                \
            .addStaticProperty(                                                \
                "class_name", +[]() { return #name; }                          \
            )                                                                  \
            .endClass();                                                       \
    }

UCLASS(Abstract)
/**
 * @brief Super class for all objects stored in database
 */
class UPrototype : public UObject {
    GENERATED_BODY()

  public:
    /**
     * @brief Object name in database
     */
    std::string name;

    virtual void lua_postprocess(ModLoadingContext &context);

  public:
    EVO_LUA_CODEGEN_DB_EX(Prototype);
    static void lua_reg(lua_State *L);

    /*!
     * @fn static This * find(std::string_view name)
     * @brief Try to find object of type This with given name
     * If there is no such object nullptr will be returned
     */

    /*!
     * @fn static This * get(std::string_view name)
     * @brief Find or create new object of type This with given name
     */

    /*!
     * @fn static This * cast(UPrototype * proto)
     * @brief Try to cast any prototype object to This type
     * If it is impossible nullptr will be returned
     */
};