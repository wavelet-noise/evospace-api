// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Prototype.h"
#include "Evospace/Blocks/ItemHopperInterface.h"
#include "Public/TieredBlockLogic.h"

#include "AbstractCrafter.generated.h"

class URecipe;
class UBaseRecipeDictionary;
class UAutosizeInventory;
class UInventoryContainer;

UCLASS(BlueprintType)
/**
 * 
 */
class EVOSPACE_API UAbstractCrafter : public UTieredBlockLogic, public ISwitchInterface {
  using Self = UAbstractCrafter;
  GENERATED_BODY()

  public:
  UAbstractCrafter();

  //
  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

  UFUNCTION(BlueprintCallable)
  virtual UBaseRecipeDictionary *GetRecipeDictionary() const;

  UFUNCTION(BlueprintCallable)
  virtual URecipe *GetCurrentRecipe() const;

  UFUNCTION(BlueprintCallable)
  virtual void SelectRecipe(APlayerController *pc, int32 i);

  UFUNCTION(BlueprintCallable)
  virtual void FindRecipe(APlayerController *pc, const UStaticItem *i);

  UFUNCTION(BlueprintCallable)
  virtual void ResetRecipe();

  UFUNCTION(BlueprintCallable)
  virtual float GetCurrentProgress() const;

  UFUNCTION(BlueprintCallable)
  virtual int32 GetSpeedLevel() const;

  UPROPERTY(BlueprintReadOnly)
  bool mLockedInput = false;

  UFUNCTION(BlueprintCallable)
  virtual int32 GetRecipeTicks(int32 &plevel) const;

  virtual void OnCraftPerformed();

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventoryContainer *mCrafterInputContainer;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventoryContainer *mCrafterOutputContainer;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UAutosizeInventory *mRecipeListTierHelper = nullptr;

  virtual bool IsBlockTicks() const override;

  UFUNCTION(BlueprintCallable)
  virtual bool IsUniversalCrafter() const;

  void SetSwitched(bool val) override;
  bool GetSwitched() const override;

  virtual void ReplaceWith(UBlockLogic *other) override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool busy = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool outputError = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool inputError = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool mLoadIndependent = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool mInputGathered = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool mSwitchedOn = true;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 ticksPassed = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 realTicksPassed = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 inputTicks = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 outputTicks = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 toLoss = 1;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int64 outputExcess = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int64 inputToGet = 0;

  protected:
  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  UBaseRecipeDictionary *mRecipeDictionary;

  friend class UBlockModdingLuaState;

  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  const URecipe *mCurrentRecipe = nullptr;

  EVO_LUA_CODEGEN_DB_EX(AbstractCrafter, BlockLogic);
  virtual void lua_reg(lua_State *L) const override {
    luabridge::getGlobalNamespace(L)
      .deriveClass<Self, UTieredBlockLogic>("AbstractCrafter")
      .addProperty("busy", &Self::busy, true)
      .addProperty("outputError", &Self::outputError, true)
      .addProperty("inputError", &Self::outputError, true)
      .addProperty("load_independent", &Self::mLoadIndependent, true)
      .addProperty("input_gathered", &Self::mInputGathered, true)
      .addProperty("switched_on", &Self::mSwitchedOn, true)
      .addProperty("ticks_passed", &Self::ticksPassed, true)
      .addProperty("real_ticks_passed", &Self::realTicksPassed, true)
      .addProperty("output_ticks", &Self::outputTicks, true)
      .addProperty("to_loss", &Self::toLoss, true)
      .addProperty("output_excess", &Self::outputExcess, true)
      .addProperty("input_to_get", &Self::inputToGet, true)
      .endClass();
  }
};