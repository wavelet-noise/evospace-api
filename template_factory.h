#pragma once

#include "ThirdParty/ecs.h"
#include "ThirdParty/lua/lua.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <utility>

/*
template<typename Ty_>
        struct EcsComponentBase {
                static auto GetPrototypeLambda() {
                        return [](ecs::Entity* e, void * proto) {
e->assign_prototype<Ty_>(*reinterpret_cast<Ty_ *>(proto)); };
                }
                static auto GetComponentLambda() {
                        return [](ecs::Entity* e) -> void * { return
e->get_ptr<Ty_>(); };
                }
                static auto GetAnyLambda() {
                        return [](void ** data) { *data = new Ty_(); };
                }
                static auto GetLuaLambda() {
                        return [](lua_State* state, void * data) {
std::error_code er; luabridge::push(state, reinterpret_cast<Ty_ *>(data), er);
                }; }
        };
*/

namespace evo {
template <class IdType, class Base, class Comparator> class TemplateFactory {
  public:
    using IdTypeUsing = IdType;

    // Register lua class in lua state
    using RegisterFunc = std::function<void(lua_State *)>;

    // Assign component prototype to entity
    using PrototypeFunc = std::function<void(ecs::Entity *, void *)>;

    // Create any class
    using AnyFunction = std::function<void(void **)>;

    // Copy any class
    using CopyAnyFunction = std::function<void *(void *)>;

    // Get named component
    using ComponentFunction = std::function<void *(ecs::Entity *)>;

    // Push any class into lua stack
    using LuaFunction = std::function<void(lua_State *, void *)>;

    using BaseFuncTuple = std::tuple<RegisterFunc, LuaFunction>;
    using ComponentFuncTuple = std::tuple<
        RegisterFunc, PrototypeFunc, LuaFunction, AnyFunction,
        ComponentFunction, CopyAnyFunction>;

    using FactoryBaseMap = std::map<IdType, BaseFuncTuple, Comparator>;
    using FactoryComponentMap =
        std::map<IdType, ComponentFuncTuple, Comparator>;

    std::optional<ComponentFuncTuple> GetComponentTuple(const IdType &id) {
        auto it = map_.find(id);
        if (it != map_.end())
            return it->second;

        return {};
    }

    BaseFuncTuple GetBaseTuple(const IdType &id) {
        auto it = base_map_.find(id);
        if (it != base_map_.end())
            return it->second;

        return {};
    }

    void registerLua(lua_State *state) const {
        for (const auto &[key, value] : map_) {
            std::get<RegisterFunc>(value)(state);
        }

        for (const auto &[key, value] : base_map_) {
            std::get<RegisterFunc>(value)(state);
        }
    }

    void componentCheckDraw(ecs::Entity *ent) const {}

    void AddComponent(
        const IdType &id, RegisterFunc reg, PrototypeFunc proto,
        LuaFunction lua, AnyFunction any, ComponentFunction comp,
        CopyAnyFunction cany, std::string_view comment = ""
    ) {
        auto i = map_.find(id);
        if (i == map_.end()) {
            map_.insert(std::make_pair(
                id, std::make_tuple(reg, proto, lua, any, comp, cany)
            ));
        } else {
            std::cout << id << "component redefinition!" << std::endl;
            i->second = std::make_tuple(reg, proto, lua, any, comp, cany);
        }
    }

    void AddBase(
        const IdType &id, RegisterFunc reg, LuaFunction lua,
        std::string_view comment = ""
    ) {
        auto i = base_map_.find(id);
        if (i == base_map_.end()) {
            base_map_.insert(
                std::make_pair(id, std::make_tuple(reg, lua))
            );
        } else {
            std::cout << id << "base redefinition!" << std::endl;
            i->second = std::make_tuple(reg, lua);
        }
    }

    FactoryComponentMap map_;
    FactoryBaseMap base_map_;
};

template <class T> class RegisterComponent {
  public:
    template <class Factory>
    RegisterComponent(
        Factory &factory, const typename Factory::IdTypeUsing &id
    ) {
        factory.AddComponent(
            id,
            T::GetRegisterLambda(),
            T::GetPrototypeLambda(),
            T::GetLuaLambda(),
            T::GetAnyLambda(),
            T::GetComponentLambda(),
            T::GetCopyAnyLambda()
        );
    }
};

template <class T> class RegisterBase {
  public:
    template <class Factory>
    RegisterBase(Factory &factory, const typename Factory::IdTypeUsing &id) {
        factory.AddBase(id, T::GetRegisterLambda(), T::GetLuaLambda());
    }
};

#define ECS_REGISTER_COMPONENT_IMPL(type, factory, id)                         \
    namespace {                                                                \
    evo::RegisterComponent<type> RegisterComponent##type(factory, id);              \
    }

#define ECS_REGISTER_BASE_IMPL(type, factory, id)                              \
    namespace {                                                                \
    evo::RegisterBase<type> RegisterBase##type(factory, id);                        \
    }
} // namespace evo