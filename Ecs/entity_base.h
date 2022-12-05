#pragma once

#include "Evospace/CoordinateSystem.h"
#include "Evospace/Shared/template_factory.h"
#include "Evospace/Shared/ThirdParty/ecs.h"
#include "Evospace/Shared/ThirdParty/luabridge.h"

class UInventory;

namespace ECS {

ECS_TYPE_IMPLEMENTATION

struct EntityFactory
{
    struct cmpNameFast {
        bool operator()(const std::string& a, const std::string& b) const {
            return a < b;
        }
    };

    using FactoryType = evo::TemplateFactory<std::string, ECS::Entity, cmpNameFast>;

    static FactoryType& Get()
    {
        static FactoryType object;
        return object;
    }
};

#define ECS_REGISTER_COMPONENT(type) ECS_REGISTER_COMPONENT_IMPL(type, ECS::EntityFactory::Get(), #type)

namespace Events {
struct OnEntitySpawned
{
    ECS_DECLARE_TYPE;

    Entity* entity;
};
}



//! Reflection helper class base for Entity components
template<typename Ty_>
struct EcsComponentBase {
    static auto GetPrototypeLambda() {
        return [](ECS::Entity* e, void* proto) { e->assign_prototype<Ty_>(*static_cast<Ty_*>(proto)); };
    }
    static auto GetComponentLambda() {
        return [](ECS::Entity* e) -> void* { return e->get_ptr<Ty_>(); };
    }
    static auto GetAnyLambda() {
        return [](void** data) { *data = new Ty_(); };
    }
    static auto GetLuaLambda() {
        return [](lua_State* state, void* data) { std::error_code er; luabridge::push(state, static_cast<Ty_*>(data), er);};
    }
    static auto GetCopyAnyLambda() {
        return [](void* data) { return new Ty_(*static_cast<Ty_*>(data)); };
    }
};

//! Position component for all Entity in Dimension
struct Core : EcsComponentBase<Core>
{
    Core(const Vec3i & val) : pos(val) {}
    Core() = default;

    Vec3i pos;

    static std::function<void(lua_State*)> GetRegisterLambda() {
        return {};
    }

    ECS_DECLARE_TYPE;
};
ECS_REGISTER_COMPONENT(Core);
ECS_DEFINE_TYPE(Core);

//! Block inventory
struct Inventory : EcsComponentBase<Inventory>
{
    Inventory(UInventory * val) : inventory(val) {}
    Inventory() = default;

    UInventory * inventory = nullptr;

    static std::function<void(lua_State*)> GetRegisterLambda() {
        return {};
    }

    ECS_DECLARE_TYPE;
};
ECS_REGISTER_COMPONENT(Inventory);
ECS_DEFINE_TYPE(Inventory);

struct Autocrafter : EcsComponentBase<Autocrafter>
{
    Autocrafter() = default;

    static std::function<void(lua_State*)> GetRegisterLambda() {
        return {};
    }

    ECS_DECLARE_TYPE;
};
ECS_REGISTER_COMPONENT(Autocrafter);
ECS_DEFINE_TYPE(Autocrafter);

#undef ECS_REGISTER_ENTITY

}

