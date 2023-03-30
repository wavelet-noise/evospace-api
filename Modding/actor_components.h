#pragma once
#include "lua_state.h"
#include "Components/AudioComponent.h"
#include "Core/item_data.h"
#include "Core/recipe.h"
#include "Evospace/IcoGenerator.h"
#include "Particles/ParticleSystemComponent.h"
#include "ThirdParty/lua/lua.h"
#include "ThirdParty/luabridge/luabridge.h"

class UIcoGenerator;

inline void registerComponentClasses(lua_State *L) {
    luabridge::getGlobalNamespace(L)
    .beginClass<UIcoGenerator>("IcoGenerator")
    .addStaticFunction("combine", &UIcoGenerator::combine)
    .endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<UTexture2D>("Texture")
        .addStaticFunction("find", &evo::LuaState::find_texture)
        .endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<UMaterialInterface>("Material")
        .addStaticFunction("load", &evo::LuaState::find_material)
        .endClass();

    luabridge::getGlobalNamespace(L).beginClass<UStaticMesh>("Mesh").endClass();

    luabridge::getGlobalNamespace(L).beginClass<UObject>("Object").endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<UClass>("Class")
        .addStaticFunction("find", &evo::LuaState::find_class)
        .addStaticFunction("load", &evo::LuaState::load_class)
        .endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<APlayerController>("PlayerController")
        .endClass();

    luabridge::getGlobalNamespace(L)
    .beginClass<KeyTable>("Loc")
    .addStaticFunction("new", &KeyTable::create)
    .addStaticFunction("new_param", &KeyTable::new_param)
    .endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<FItemData>("ItemData")
        .addStaticFunction(
            "new_empty", +[]() { return FItemData(); }
        )
        .addStaticFunction(
            "new",
            +[](UItem *item, int64 count) { return FItemData(item, count); }
        )
        .addStaticFunction(
            "new_zero", +[](UItem *item) { return FItemData(item); }
        )
        .addProperty("count", &FItemData::count)
        .addProperty("item", &FItemData::item)
        .endClass();

    luabridge::getGlobalNamespace(L)
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

    luabridge::getGlobalNamespace(L)
        .beginClass<UActorComponent>("ActorComponent")
        .addProperty("name", [](UActorComponent * comp){ return std::string(TCHAR_TO_UTF8(*comp->GetName())); })
        .endClass();

    luabridge::getGlobalNamespace(L)
        .deriveClass<UParticleSystemComponent, UActorComponent>("ParticleSystemComponent")
        .addStaticFunction("class", [](){ return UParticleSystemComponent::StaticClass(); })
        .addFunction("activate", &UParticleSystemComponent::Activate)
        .addFunction("deactivate", &UParticleSystemComponent::Deactivate)
        .addFunction("is_active", &UParticleSystemComponent::IsActive)
        .addFunction("set_template", &UParticleSystemComponent::SetTemplate)
        .addFunction("set_color_parameter", &UParticleSystemComponent::SetColorParameter)
        .addFunction("set_float_parameter", &UParticleSystemComponent::SetFloatParameter)
        .addFunction("set_material_parameter", &UParticleSystemComponent::SetMaterialParameter)
        .addFunction("set_vector_parameter", &UParticleSystemComponent::SetVectorParameter)
        //.addProperty("auto_activate", &UParticleSystemComponent::bAutoActivate)
        .addProperty("template", &UParticleSystemComponent::Template)
        .endClass();

    luabridge::getGlobalNamespace(L)
        .deriveClass<UAudioComponent, UActorComponent>("AudioComponent")
        .addStaticFunction("class", [](){ return UActorComponent::StaticClass(); })
        .addFunction("play", &UAudioComponent::Play)
        .addFunction("stop", &UAudioComponent::Stop)
        .addFunction("fade_in", &UAudioComponent::FadeIn)
        .addFunction("fade_out", &UAudioComponent::FadeOut)
        .addFunction("set_pitch_multiplier", &UAudioComponent::SetPitchMultiplier)
        .addFunction("set_volume_multiplier", &UAudioComponent::SetVolumeMultiplier)
        .addProperty("sound", &UAudioComponent::Sound)
        .addProperty("is_playing", &UAudioComponent::IsPlaying)
        .endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<AActor>("Actor")
        .addFunction("add_actor_component", [](AActor* actor, UClass* componentClass, const std::string& componentName) {
            if (actor && componentClass) {
                UActorComponent* newComponent = NewObject<UActorComponent>(actor, componentClass, FName(UTF8_TO_TCHAR(componentName.data())));
                if (newComponent) {
                    newComponent->RegisterComponent();
                    actor->AddInstanceComponent(newComponent);
                    return newComponent;
                }
            }
            return static_cast<UActorComponent*>(nullptr);
        })
        .endClass();
}
