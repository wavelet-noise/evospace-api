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
        luabridge::getGlobalNamespace(L)                                       \
            .beginClass<type>(#name)                                           \
            .addStaticFunction("find", &evo::DB::find_mut<type>)               \
            .addStaticFunction("get", &evo::DB::get<type>)                     \
            .addStaticFunction("get_derived", &evo::DB::get_derived<type>)     \
            .addStaticFunction("cast", &type::lua_codegen_cast)                \
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
};