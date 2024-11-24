// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Prototype.h"
#include "Evospace/Blocks/ItemHopperInterface.h"
#include "Public/TieredBlockLogic.h"

#include "AbstractCrafter.generated.h"

class UResourceInventory;
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
  EVO_CODEGEN_INSTANCE(AbstractCrafter);
  virtual void lua_reg(lua_State *L) const override {
    luabridge::getGlobalNamespace(L)
      .deriveClass<Self, UTieredBlockLogic>("AbstractCrafter")
      .addProperty("load_independent", &Self::mLoadIndependent)
      .addProperty("input_gathered", &Self::mInputGathered)
      .addProperty("switched_on", &Self::mSwitchedOn)
      .addProperty("ticks_passed", &Self::mTicksPassed)
      .addProperty("real_ticks_passed", &Self::mRealTicksPassed)
      .addProperty("total_production", &Self::mTotalProduction)
      .addProperty("speed", &Self::mSpeed)

      .addProperty("energy_input_inventory", &Self::mEnergyInputInventory)
      .addProperty("energy_output_inventory", &Self::mEnergyOutputInventory)

      .addProperty("crafter_input_container", &Self::mCrafterInputContainer)
      .addProperty("crafter_output_container", &Self::mEnergyOutputInventory)
      .endClass();
  }

  public:
  UAbstractCrafter();

  UFUNCTION(BlueprintCallable, BlueprintCosmetic)
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

  UFUNCTION(BlueprintCallable, BlueprintCosmetic)
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
  UInventoryContainer *mCrafterInputContainer = nullptr;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventoryContainer *mCrafterOutputContainer = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UResourceInventory *mEnergyInputInventory = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UResourceInventory *mEnergyOutputInventory = nullptr;

  //TODO: do we need this?
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UAutosizeInventory *mRecipeListTierHelper = nullptr;

  TArray<class UResourceAccessor *> GetResourceInputAccessors() const;
  TArray<class UResourceAccessor *> GetResourceOutputAccessors() const;

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
  int32 mSpeed = 100;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  ECrafterState mState = ECrafterState::InputShortage;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 mInputTicks = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 mOutputTicks = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 mCollectedProductivity = 0;

  protected:
  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  UBaseRecipeDictionary *mRecipeDictionary;

  friend class UBlockModdingLuaState;

  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  const URecipe *mCurrentRecipe = nullptr;
};