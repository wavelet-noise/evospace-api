// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once

#include "ThirdParty/luabridge/LuaBridge.h"
#include "StaticLogger.h"
#include "Evospace/JsonObjectLibrary.h"
#include "Evospace/MainGameOwner.h"
#include "Evospace/SerializableJson.h"
#include "Logging/StructuredLog.h"

#include "prototype.generated.h"

class UMod;
class Base;

/*.addStaticFunction("get", &evo::DB::get<U##type>) */ /*.addStaticFunction("get_derived", &evo::DB::get_derived<U##type>) */
#define EVO_CODEGEN_DB(type, topmost_not_prototype)                                                                                                           \
  public:                                                                                                                                                     \
  virtual UClass *lua_reg_type() {                                                                                                                            \
    return U##type::StaticClass();                                                                                                                            \
  }                                                                                                                                                           \
  virtual UObject *get_or_register(const FString &obj_name, IRegistrar &registry) override {                                                                  \
    return _get_or_register<U##topmost_not_prototype, U##type>(obj_name, registry);                                                                           \
  }                                                                                                                                                           \
  static U##type *lua_codegen_cast(UObject *parent_inst) {                                                                                                    \
    return Cast<U##type>(parent_inst);                                                                                                                        \
  }                                                                                                                                                           \
  virtual void lua_reg_internal(lua_State *L) const override {                                                                                                \
    LOG(INFO_LL) << "Registering lua prototype " << TEXT(#type);                                                                                              \
    luabridge::getGlobalNamespace(L)                                                                                                                          \
      .beginClass<U##type>(#type)                                                                                                                             \
      .addStaticFunction(                                                                                                                                     \
        "find", +[](std::string_view name) { return FindObject<U##type>(MainGameOwner<U##topmost_not_prototype>::Get(), UTF8_TO_TCHAR(name.data())); })       \
      .addStaticFunction("cast", &U##type::lua_codegen_cast)                                                                                                  \
      .addStaticFunction("get_class", []() { return U##type::StaticClass(); })                                                                                \
      .addFunction("__tostring", &U##type::ToString)                                                                                                          \
      .endClass();                                                                                                                                            \
    if (!U##type::StaticClass()->HasAnyClassFlags(CLASS_Abstract)) {                                                                                          \
      luabridge::getGlobalNamespace(L)                                                                                                                        \
        .beginClass<U##type>(#type)                                                                                                                           \
        .addStaticFunction(                                                                                                                                   \
          "reg", +[](std::string_view newName) { return NewObject<U##type>(MainGameOwner<U##topmost_not_prototype>::Get(), UTF8_TO_TCHAR(newName.data())); }) \
        .endClass();                                                                                                                                          \
    }                                                                                                                                                         \
  }

#define EVO_CODEGEN_INSTANCE(type)                                                                                                     \
  public:                                                                                                                              \
  virtual UClass *lua_reg_type() {                                                                                                     \
    return U##type::StaticClass();                                                                                                     \
  }                                                                                                                                    \
  static U##type *lua_codegen_cast(UObject *parent_inst) {                                                                             \
    return Cast<U##type>(parent_inst);                                                                                                 \
  }                                                                                                                                    \
  virtual void lua_reg_internal(lua_State *L) const override {                                                                         \
    LOG(INFO_LL) << "Registering lua instance " << TEXT(#type);                                                                        \
    luabridge::getGlobalNamespace(L)                                                                                                   \
      .beginClass<U##type>(#type)                                                                                                      \
      .addStaticFunction("cast", &U##type::lua_codegen_cast)                                                                           \
      .addStaticFunction("get_class", []() { return U##type::StaticClass(); })                                                         \
      .addFunction("__tostring", &U##type::ToString)                                                                                   \
      .endClass();                                                                                                                     \
    if (!U##type::StaticClass()->HasAnyClassFlags(CLASS_Abstract)) {                                                                   \
      luabridge::getGlobalNamespace(L)                                                                                                 \
        .beginClass<U##type>(#type)                                                                                                    \
        .addStaticFunction(                                                                                                            \
          "new", +[](UObject *parent, std::string_view newName) { return NewObject<U##type>(parent, UTF8_TO_TCHAR(newName.data())); }) \
        .endClass();                                                                                                                   \
    }                                                                                                                                  \
  }

// /*.addStaticFunction("get", &evo::DB::get<type>)   */ /* .addStaticFunction("get_derived", &evo::DB::get_derived<type>)  */
// #define EVO_LUA_CODEGEN_EMPTY(type, parent, name)                                                                           \
//   public:                                                                                                                   \
//   static void lua_reg(lua_State *L) {                                                                                       \
//     LOG(INFO_LL) << "Registering lua " << #name;                                                                            \
//     luabridge::getGlobalNamespace(L)                                                                                        \
//       .deriveClass<type, parent>(#name)                                                                                     \
//       .addStaticFunction(                                                                                                   \
//         "find", +[](std::string_view name) { return FindObject<type>(EVO_ASSET_OWNER(), UTF8_TO_TCHAR(name.data())); })     \
//       .addStaticFunction("cast", &type::lua_codegen_cast)                                                                   \
//       .addStaticFunction(                                                                                                   \
//         "new", +[](std::string_view newName) { return NewObject<type>(EVO_ASSET_OWNER(), UTF8_TO_TCHAR(newName.data())); }) \
//       .addStaticFunction("get_class", []() { return type::StaticClass(); })                                                 \
//       .endClass();                                                                                                          \
//   }

UCLASS(Abstract)
/**
 * @brief Super class for all objects stored in database
 */
class UPrototype : public UObject, public ISerializableJson {
  GENERATED_BODY()

  public:
  static UPrototype *lua_codegen_cast(UObject *parent_inst) { return Cast<UPrototype>(parent_inst); }
  virtual UClass *lua_reg_type() { return UPrototype::StaticClass(); }
  virtual void register_owner() {}
  virtual void lua_reg_internal(lua_State *L) const {
    LOG(INFO_LL) << "Registering lua "
                 << "Prototype";
    luabridge::getGlobalNamespace(L)
      .deriveClass<UPrototype, UObject>("Prototype")

      .endClass();
  };
  virtual void lua_reg(lua_State *L) const {
    luabridge::getGlobalNamespace(L)
      .deriveClass<UPrototype, UObject>("Prototype")
      .endClass();
  }

  UPROPERTY(VisibleAnywhere)
  const UMod *mOwningMod = nullptr;

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override {
    return true;
  }

  virtual void LuaCleanup() {}

  virtual void MarkIncomplete() {}

  virtual std::string ToString() const {
    return TCHAR_TO_UTF8(*("(" + GetClass()->GetName() + ": " + GetName() + ")"));
  }

  virtual UObject *get_or_register(const FString &obj_name, IRegistrar &registry) {
    checkNoEntry();
    return nullptr;
  }

  protected:
  template <typename BaseType, typename RealType>
  inline UObject *_get_or_register(const FString &obj_name, IRegistrar &registry) {
    auto obj = FindObject<BaseType>(MainGameOwner<BaseType>::Get(), *obj_name);
    if (!obj) {
      obj = NewObject<BaseType>(MainGameOwner<BaseType>::Get(), RealType::StaticClass(), *obj_name);
      LOG(INFO_LL) << "Register " << BaseType::StaticClass()->GetName() << " " << obj_name;
      registry.Register(obj);
    }

    return obj;
  }
};

UCLASS(Abstract)
/**
 * @brief Super class for all object instances 
 */
class UInstance : public UObject, public ISerializableJson {
  GENERATED_BODY()

  public:
  static UInstance *lua_codegen_cast(UObject *parent_inst) { return Cast<UInstance>(parent_inst); }
  virtual UClass *lua_reg_type() { return UInstance::StaticClass(); }
  virtual void register_owner() {}
  virtual void lua_reg_internal(lua_State *L) const {
    LOG(INFO_LL) << "Registering lua "
                 << "Prototype";
    luabridge::getGlobalNamespace(L)
      .deriveClass<UInstance, UObject>("Instance")

      .endClass();
  };
  virtual void lua_reg(lua_State *L) const {
    luabridge::getGlobalNamespace(L)
      .deriveClass<UInstance, UObject>("Instance")
      .endClass();
  }

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override {
    return true;
  }

  virtual void LuaCleanup() {}

  virtual std::string ToString() const {
    return TCHAR_TO_UTF8(*("(" + GetClass()->GetName() + ": " + GetName() + ")"));
  }
};