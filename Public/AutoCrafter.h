// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Public/SelectCrafter.h"
#include "CoreMinimal.h"
#include "Evospace/Blocks/ItemHopperInterface.h"

#include "AutoCrafter.generated.h"

class UAutosizeInventory;
class UInventory;

UCLASS(BlueprintType)
/**
 * 
 */
class EVOSPACE_API UAutoCrafter : public USelectCrafter {
  using Self = UAutoCrafter;
  GENERATED_BODY()

  protected:
  UAutoCrafter();

  virtual void Tick() override;

  UPROPERTY()
  class UNonSerializedAutosizeInventory *mLastInventory;

  public:
  virtual bool IsUniversalCrafter() const override;

  virtual void SelectRecipe(APlayerController *pc, int32 i) override;

  virtual void LoadSettings(TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr) override;

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  virtual void BlockBeginPlay() override;

  int32 cap_replace = 0;

  EVO_CODEGEN_INSTANCE(AutoCrafter)
  virtual void lua_reg(lua_State *L) const override {
    luabridge::getGlobalNamespace(L)
      .deriveClass<Self, USelectCrafter>("AutoCrafter")
      .endClass();
  }
};

UCLASS(BlueprintType)
class EVOSPACE_API UDeconstructorCrafterBlockLogic
  : public UAutoCrafter {
  GENERATED_BODY()

  public:
  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
};

UCLASS(BlueprintType)
class EVOSPACE_API UDumpAnyBlockLogic : public UTieredBlockLogic, public ISwitchInterface {
  GENERATED_BODY()

  public:
  UDumpAnyBlockLogic();

  virtual void Tick() override;

  virtual bool IsBlockTicks() const override;

  virtual void BlockBeginPlay() override;

  void SetActor(ABlockActor *actor);
  FObjectProperty *mItem = nullptr;

  virtual void SetWorking(bool working);
  FBoolProperty *mWorking = nullptr;

  void SetSwitched(bool val) override;

  bool GetSwitched() const override;

  protected:
  UPROPERTY()
  UInventory *mInputInventory;

  bool mSwitchedOn = true;

  int32 AnimationTicks = 0;

  public:
  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;
};

UCLASS(BlueprintType)
class EVOSPACE_API UDumpCrafterBlockLogic : public USelectCrafter {
  GENERATED_BODY()

  protected:
  virtual void Tick() override;

  virtual void BlockBeginPlay() override;

  void SetActor(ABlockActor *actor);
  FObjectProperty *mItem = nullptr;

  public:
  virtual bool IsUniversalCrafter() const override;

  virtual void SelectRecipe(APlayerController *pc, int32 i) override;

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  int32 AnimationTicks = 0;
};