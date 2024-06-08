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
class UStaticTip : public UPrototype {
  GENERATED_BODY()
  public:
  UStaticTip();

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  FKeyTableObject mLabel;

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  FKeyTableObject mDescription;

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  UAutosizeInventory *mContextInventory;

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  UTexture2D *mImage;

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  FString mImagePath;

  UFUNCTION(BlueprintCallable)
  void LoadImagePath();

  void AddContext(const UStaticItem *item);
  void ClearContext();

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  EVO_LUA_CODEGEN_DB_EX(StaticTip);
  static void lua_reg(lua_State *L) {
    luabridge::getGlobalNamespace(L)
      .deriveClass<UStaticTip, UPrototype>("StaticTip")
      .addProperty("label", &UStaticTip::mLabel)
      .addProperty("description", &UStaticTip::mDescription)
      .addProperty("image", &UStaticTip::mImagePath)
      .addFunction("add_context", &UStaticTip::AddContext)
      .addFunction("clear_context", &UStaticTip::ClearContext)
      .endClass();
  }

  EVO_GET_OR_REGISTER(UStaticTip, UStaticTip);
};
