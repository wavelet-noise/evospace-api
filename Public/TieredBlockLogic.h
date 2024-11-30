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
  EVO_CODEGEN_INSTANCE(TieredBlockLogic)
  virtual void lua_reg(lua_State *L) const override {
    luabridge::getGlobalNamespace(L)
      .deriveClass<Self, UBlockLogic>("TieredBlockLogic")
      .addProperty("tier", &Self::Tier)
      .addProperty("level", &Self::Level)
      .endClass();
  }

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
  uint8 Tier = 0;

  UPROPERTY(BlueprintReadOnly, EditAnywhere)
  uint8 Level = 0;

  UFUNCTION(BlueprintCallable)
  static FString TierToString(int32 t);

  UFUNCTION(BlueprintCallable)
  static FColor TierToColor(int32 t);
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
