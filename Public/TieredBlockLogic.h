// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Public/BlockLogic.h"

#include "TieredBlockLogic.generated.h"

class UInventoryReader;

UCLASS(BlueprintType)
/**
 * 
 */
class EVOSPACE_API UTieredBlockLogic : public UBlockLogic {
  using Self = UTieredBlockLogic;
  GENERATED_BODY()

  public:
  UTieredBlockLogic();

  // Has actual code
  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  // Has actual code
  virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

  UFUNCTION(BlueprintCallable)
  uint8 GetTier() const;

  UFUNCTION(BlueprintCallable)
  uint8 GetLevel() const;

  virtual void SetActor(ABlockActor *actor) override;

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  uint8 mTier = 0;

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  uint8 mLevel = 0;

  protected:
  static FString TierToString(int32 tier);

  EVO_LUA_CODEGEN_DB_EX(TieredBlockLogic);
  static void lua_reg(lua_State *L) {
    luabridge::getGlobalNamespace(L)
      .deriveClass<Self, UBlockLogic>("TieredBlockLogic")
      .addProperty("tier", &Self::mTier)
      .addProperty("level", &Self::mLevel)
      .endClass();
  }
};

UCLASS(BlueprintType)
class EVOSPACE_API UFilteringBlockLogic : public UTieredBlockLogic {
  GENERATED_BODY()

  public:
  UFUNCTION(BlueprintCallable)
  virtual void ChangeFilter(int32 inventory, int32 slot, UStaticItem *item) {}

  UFUNCTION(BlueprintCallable)
  virtual UInventory *GetOwnInventory() { return nullptr; }
};
