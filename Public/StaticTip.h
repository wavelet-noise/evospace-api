#pragma once
#include "Prototype.h"
#include "Evospace/Common.h"
#include "Evospace/SerializableJson.h"
#include "StaticTip.generated.h"

class UAutosizeInventory;
class UMainGameModLoader;

UCLASS(BlueprintType)
/**
 * 
 */
class UStaticTip : public UObject, public ISerializableJson {
  GENERATED_BODY()
  public:
  UStaticTip();

  UPROPERTY(BlueprintReadOnly)
  FKeyTableObject mLabel;

  UPROPERTY(BlueprintReadOnly)
  FKeyTableObject mDescription;

  UPROPERTY()
  UAutosizeInventory *mContextInventory;

  void AddContext(const UStaticItem *item);
  void ClearContext();

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  EVO_LUA_CODEGEN_DB_EX(StaticTip);
  static void lua_reg(lua_State *L) {
    luabridge::getGlobalNamespace(L)
      .deriveClass<UStaticTip, UObject>("StaticTip")
      .addProperty("label", &UStaticTip::mLabel)
      .addProperty("description", &UStaticTip::mDescription)
      .addFunction("add_context", &UStaticTip::AddContext)
      .addFunction("clear_context", &UStaticTip::ClearContext)
      .endClass();
  }
};
