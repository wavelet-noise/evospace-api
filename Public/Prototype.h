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
#define EVO_CODEGEN(type, parent)                                                                                                            \
  public:                                                                                                                                    \
  virtual UClass *lua_reg_type() {                                                                                                           \
    return U##type::StaticClass();                                                                                                           \
  }                                                                                                                                          \
  virtual UObject *get_or_register(const FString &obj_name, IRegistrar &registry) override {                                                 \
    return _get_or_register<U##parent, U##type>(obj_name, registry);                                                                         \
  }                                                                                                                                          \
  static U##type *lua_codegen_cast(UObject *parent_inst) {                                                                                   \
    return Cast<U##type>(parent_inst);                                                                                                       \
  }                                                                                                                                          \
  virtual void lua_reg_internal(lua_State *L) const override {                                                                               \
    LOG(INFO_LL) << u"Registering lua " << TEXT(#type);                                                                                      \
    luabridge::getGlobalNamespace(L)                                                                                                         \
      .beginClass<U##type>(#type)                                                                                                            \
      .addStaticFunction(                                                                                                                    \
        "find", +[](std::string_view name) { return FindObject<U##type>(MainGameOwner<U##parent>::Get(), UTF8_TO_TCHAR(name.data())); })     \
      .addStaticFunction("cast", &U##type::lua_codegen_cast)                                                                                 \
      .addStaticFunction(                                                                                                                    \
        "new", +[](std::string_view newName) { return NewObject<U##type>(MainGameOwner<U##parent>::Get(), UTF8_TO_TCHAR(newName.data())); }) \
      .addStaticFunction("get_class", []() { return U##type::StaticClass(); })                                                               \
      .addFunction("__tostring", &U##type::ToString)                                                                                         \
      .endClass();                                                                                                                           \
  }

// /*.addStaticFunction("get", &evo::DB::get<type>)   */ /* .addStaticFunction("get_derived", &evo::DB::get_derived<type>)  */
// #define EVO_LUA_CODEGEN_EMPTY(type, parent, name)                                                                           \
//   public:                                                                                                                   \
//   static void lua_reg(lua_State *L) {                                                                                       \
//     LOG(INFO_LL) << u"Registering lua " << #name;                                                                            \
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
  /**
     * @brief Object name in database
     */
  //std::string name;

  //virtual void lua_postprocess(ModLoadingContext &context);

  public:
  static UPrototype *lua_codegen_cast(UObject *parent_inst) { return Cast<UPrototype>(parent_inst); }
  virtual UClass *lua_reg_type() { return UPrototype::StaticClass(); }
  virtual void lua_reg_internal(lua_State *L) const {
    LOG(INFO_LL) << u"Registering lua " << u"Prototype";
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

  protected:
  template <typename BaseType, typename RealType>
  inline UObject *_get_or_register(const FString &obj_name, IRegistrar &registry) {
    auto obj = FindObject<BaseType>(MainGameOwner<BaseType>::Get(), *obj_name);
    if (!obj) {
      obj = NewObject<BaseType>(MainGameOwner<BaseType>::Get(), RealType::StaticClass(), *obj_name);
      UE_LOGFMT(LogLoad, Display, "Register {0} {1}", BaseType::StaticClass()->GetName(), obj_name);
      registry.Register(obj);
    }

    return obj;
  }
};