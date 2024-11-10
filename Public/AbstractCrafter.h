// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Prototype.h"
#include "Evospace/Blocks/ItemHopperInterface.h"
#include "Public/TieredBlockLogic.h"

#include "AbstractCrafter.generated.h"

class UResourceComponent;
class URecipe;
class UBaseRecipeDictionary;
class UAutosizeInventory;
class UInventoryContainer;

UENUM(BlueprintType)
enum class ECrafterState : uint8 {
  InputShortage,
  Working,
  NoRoomInOutput,
  ResourceSaturated,
  ResourceRequired,
  NotInitialized,
  SwitchedOff,
};

UCLASS(BlueprintType)
/**
 * 
 */
class EVOSPACE_API UAbstractCrafter : public UTieredBlockLogic, public ISwitchInterface {
  using Self = UAbstractCrafter;
  GENERATED_BODY()

  public:
  UAbstractCrafter();

  FColor GetStateColor() const;

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
  virtual int32 GetProductivity() const;

  UFUNCTION(BlueprintCallable, BlueprintCosmetic)
  virtual float GetProductivityProgress() const;

  UPROPERTY(BlueprintReadOnly)
  bool mLockedInput = false;

  virtual void OnCraftPerformed();

  virtual void BlockEndPlay() override;

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
  bool mLoadIndependent = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool mInputGathered = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool mSwitchedOn = true;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 mTicksPassed = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 mRealTicksPassed = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 mTotalProduction = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 mToLoss = 1;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  ECrafterState mState = ECrafterState::NotInitialized;

  UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
  class UResourceComponent *mResourceComponent = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 mCollectedProductivity = 0;

  protected:
  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  UBaseRecipeDictionary *mRecipeDictionary;

  friend class UBlockModdingLuaState;

  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  const URecipe *mCurrentRecipe = nullptr;

  EVO_CODEGEN(AbstractCrafter, BlockLogic);
  virtual void lua_reg(lua_State *L) const override {
    luabridge::getGlobalNamespace(L)
      .deriveClass<Self, UTieredBlockLogic>("AbstractCrafter")
      .addProperty("load_independent", &Self::mLoadIndependent, true)
      .addProperty("input_gathered", &Self::mInputGathered, true)
      .addProperty("switched_on", &Self::mSwitchedOn, true)
      .addProperty("ticks_passed", &Self::mTicksPassed, true)
      .addProperty("real_ticks_passed", &Self::mRealTicksPassed, true)
      .addProperty("to_loss", &Self::mToLoss, true)
      .addProperty("total_production", &Self::mTotalProduction, true)
      .endClass();
  }
};