#pragma once
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ThirdParty/lua/lua.h"
#include "ThirdParty/luabridge/luabridge.h"
#include "Evospace/Common.h"
#include "Evospace/Blocks/BlockActor.h"
#include "Evospace/Item/ItemData.h"
#include "Evospace/Item/Recipe.h"

class UIcoGenerator;

inline void registerComponentClasses(lua_State *L) {
  luabridge::getGlobalNamespace(L)
    .beginClass<UObject>("Object")
    .addStaticFunction(
      "find", +[](std::string_view name) { return FindObject<UObject>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data())); })
    .addStaticFunction("cast", [](UObject *obj) { return obj; })
    .addFunction("get_name", [](UObject *obj) { return std::string(TCHAR_TO_UTF8(*obj->GetName())); })
    .addFunction("get_class", [](UObject *obj) { return obj->GetClass(); })
    .addStaticFunction("get_class", []() { return UObject::StaticClass(); })
    .endClass();

  luabridge::getGlobalNamespace(L)
    .beginClass<UIcoGenerator>("IcoGenerator")
    //.addStaticFunction("combine", &UIcoGenerator::combine)
    .endClass();

  luabridge::getGlobalNamespace(L)
    .deriveClass<UTexture2D, UObject>("Texture")
    .addStaticFunction("find", &evo::LuaState::FindTexture)
    .endClass();

  luabridge::getGlobalNamespace(L)
    .deriveClass<UMaterialInterface, UObject>("Material")
    .addStaticFunction("load", &evo::LuaState::FindMaterial)
    .endClass();

  luabridge::getGlobalNamespace(L)
    .deriveClass<UStaticMesh, UObject>("StaticMesh")
    .endClass();

  luabridge::getGlobalNamespace(L)
    .deriveClass<UClass, UObject>("Class")
    .addStaticFunction("find", &evo::LuaState::FindClass)
    .addStaticFunction("load", &evo::LuaState::LoadClass)
    .addStaticFunction("cast", [](UObject *obj) { return Cast<UClass>(obj); })
    .addFunction(
      "get_name", +[](const UClass *cl) { return std::string(TCHAR_TO_UTF8(*cl->GetName())); })
    .addFunction("is_child_of", [](const UClass *self, const UClass *other) {
      return self->IsChildOf(other);
    })
    .endClass();

  luabridge::getGlobalNamespace(L)
    .beginClass<APlayerController>("PlayerController")
    .endClass();

  luabridge::getGlobalNamespace(L)
    .beginClass<FKeyTableObject>("Loc")
    .addStaticFunction("new", [](std::string_view table, std::string_view key) {
      auto kt = FKeyTableObject();
      kt.Table = UTF8_TO_TCHAR(table.data());
      kt.Key = UTF8_TO_TCHAR(key.data());
      return kt;
    })
    .addStaticFunction("new_param", [](std::string_view table, std::string_view key, float param) {
      auto kt = FKeyTableObject();
      kt.Table = UTF8_TO_TCHAR(table.data());
      kt.Key = UTF8_TO_TCHAR(key.data());
      kt.Value = param;
      kt.Args = 1;
      return kt;
    })
    .endClass();

  luabridge::getGlobalNamespace(L)
    .beginClass<FItemData>("ItemData")
    .addStaticFunction(
      "new_empty", +[]() { return FItemData(); })
    .addStaticFunction(
      "new",
      +[](UStaticItem *item, int64 count) { return FItemData(item, count); })
    .addStaticFunction(
      "new_zero", +[](UStaticItem *item) { return FItemData(item); })
    .addProperty("count", &FItemData::mValue)
    .addProperty("item", &FItemData::mItem)
    .endClass();

  luabridge::getGlobalNamespace(L)
    .beginClass<URecipe>("Recipe")
    //.addStaticFunction("new", &URecipe::lua_new)
    .addProperty("loss", &URecipe::loss)
    .addProperty("ticks", &URecipe::ticks)
    .addProperty("input", &URecipe::input, false)
    .addProperty("output", &URecipe::output, false)
    .addProperty("res_input", &URecipe::res_input)
    .addProperty("res_output", &URecipe::res_output)
    //.addProperty("name", &URecipe::get_name, &URecipe::set_name)
    .endClass();

  luabridge::getGlobalNamespace(L)
    .beginClass<UActorComponent>("ActorComponent")
    .addProperty(
      "name",
      [](UActorComponent *comp) {
        return std::string(TCHAR_TO_UTF8(*comp->GetName()));
      })
    .endClass();

  luabridge::getGlobalNamespace(L)
    .deriveClass<UParticleSystemComponent, UActorComponent>(
      "ParticleSystemComponent")
    .addStaticFunction(
      "class", []() { return UParticleSystemComponent::StaticClass(); })
    .addFunction("activate", &UParticleSystemComponent::Activate)
    .addFunction("deactivate", &UParticleSystemComponent::Deactivate)
    .addFunction("is_active", &UParticleSystemComponent::IsActive)
    .addFunction("set_template", &UParticleSystemComponent::SetTemplate)
    .addFunction(
      "set_color_parameter", &UParticleSystemComponent::SetColorParameter)
    .addFunction(
      "set_float_parameter", &UParticleSystemComponent::SetFloatParameter)
    .addFunction(
      "set_material_parameter",
      &UParticleSystemComponent::SetMaterialParameter)
    .addFunction(
      "set_vector_parameter",
      &UParticleSystemComponent::SetVectorParameter)
    //.addProperty("auto_activate",
    //&UParticleSystemComponent::bAutoActivate)
    .addProperty("template", &UParticleSystemComponent::Template)
    .endClass();

  luabridge::getGlobalNamespace(L)
    .deriveClass<UAudioComponent, UActorComponent>("AudioComponent")
    .addStaticFunction(
      "Class", []() { return UActorComponent::StaticClass(); })
    .addFunction("play", &UAudioComponent::Play)
    .addFunction("stop", &UAudioComponent::Stop)
    .addFunction("fade_in", &UAudioComponent::FadeIn)
    .addFunction("fade_out", &UAudioComponent::FadeOut)
    .addFunction(
      "set_pitch_multiplier", &UAudioComponent::SetPitchMultiplier)
    .addFunction(
      "set_volume_multiplier", &UAudioComponent::SetVolumeMultiplier)
    .addProperty("sound", &UAudioComponent::Sound)
    .addProperty("isPlaying", &UAudioComponent::IsPlaying)
    .endClass();

  luabridge::getGlobalNamespace(L)
    .beginClass<AActor>("Actor")
    .addFunction(
      "add_actor_component",
      [](AActor *actor,
         UClass *componentClass,
         const std::string &componentName) {
        if (actor && componentClass) {
          UActorComponent *newComponent = NewObject<UActorComponent>(
            actor,
            componentClass,
            FName(UTF8_TO_TCHAR(componentName.data())));
          if (newComponent) {
            newComponent->RegisterComponent();
            actor->AddInstanceComponent(newComponent);
            return newComponent;
          }
        }
        return static_cast<UActorComponent *>(nullptr);
      })
    .addFunction("set_field_object", [](AActor *actor, std::string_view field_name, UObject *object) {
      if (ensure(actor && field_name != "")) {
        auto prop = FindFProperty<FObjectPropertyBase>(actor->GetClass(),
                                                       UTF8_TO_TCHAR(field_name.data()));
        if (prop) {
          prop->SetObjectPropertyValue_InContainer(actor, object);
        }
        return true;
      }
      return false;
    })
    .endClass();

  luabridge::getGlobalNamespace(L)
    .deriveClass<ABlockActor, AActor>("BlockActor")
    .endClass();
}
