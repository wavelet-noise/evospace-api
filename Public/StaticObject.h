
// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/SerializableJson.h"
#include "Public/Prototype.h"

#include "StaticObject.generated.h"

class ADimension;
class UStaticItem;
class AActor;

USTRUCT(BlueprintType)
struct FStaticBlockMinable {
  GENERATED_BODY()

  UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
  bool mMinable = true;

  UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
  UStaticItem *mResult = nullptr;

  UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
  int32 mMiningTime = 20;

  bool DeserializeJson(TSharedPtr<FJsonObject> json);
};

UCLASS(Abstract)
class EVOSPACE_API UStaticObject : public UObject, public ISerializableJson {
  GENERATED_BODY()

  public:
  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  UPROPERTY(BlueprintReadWrite)
  UStaticItem *mStaticItem;

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  FStaticBlockMinable mMinable = {};

  UPROPERTY(BlueprintReadOnly)
  FQuat mDefaultRotation = FQuat::Identity;

  virtual void LuaCleanup() {
  }

  virtual AActor *CreateSelector() const { return nullptr; };

  EVO_LUA_CODEGEN_DB_EX(StaticObject);
  static void lua_reg(lua_State *L);
};
