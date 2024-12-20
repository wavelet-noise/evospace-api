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
class URecipeDictionary;
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
      .addProperty("recipes", &Self::RecipeDictionary)
    
      .addProperty("load_independent", &Self::LoadIndependent)
      .addProperty("input_gathered", &Self::InputGathered)
      .addProperty("switched_on", &Self::SwitchedOn)
      .addProperty("ticks_passed", &Self::TicksPassed)
      .addProperty("real_ticks_passed", &Self::RealTicksPassed)
      .addProperty("total_production", &Self::TotalProduction)
      .addProperty("speed", &Self::Speed)

      .addProperty("energy_input_inventory", &Self::EnergyInputInventory)
      .addProperty("energy_output_inventory", &Self::EnergyOutputInventory)

      .addProperty("crafter_input_container", &Self::CrafterInputContainer)
      .addProperty("crafter_output_container", &Self::EnergyOutputInventory)
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
  virtual URecipeDictionary *GetRecipeDictionary() const;

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
  bool LockedInput = false;

  virtual void OnCraftPerformed();

  virtual void BlockEndPlay() override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventoryContainer *CrafterInputContainer = nullptr;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventoryContainer *CrafterOutputContainer = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UResourceInventory *EnergyInputInventory = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UResourceInventory *EnergyOutputInventory = nullptr;

  //TODO: do we need this?
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UAutosizeInventory *RecipeListTierHelper = nullptr;

  TArray<class UResourceAccessor *> GetResourceInputAccessors() const;
  TArray<class UResourceAccessor *> GetResourceOutputAccessors() const;

  virtual bool IsBlockTicks() const override;

  UFUNCTION(BlueprintCallable)
  virtual bool IsUniversalCrafter() const;

  void SetSwitched(bool val) override;
  bool GetSwitched() const override;

  virtual void CopyOnReplace(UBlockLogic *from) override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool LoadIndependent = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool InputGathered = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  bool SwitchedOn = true;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 TicksPassed = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 RealTicksPassed = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 TotalProduction = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 Speed = 100;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  ECrafterState State = ECrafterState::InputShortage;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 InputTicks = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 OutputTicks = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 CollectedProductivity = 0;

  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  URecipeDictionary *RecipeDictionary;

  friend class UBlockModdingLuaState;

  UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
  const URecipe *CurrentRecipe = nullptr;
};