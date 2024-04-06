// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/Blocks/BlockWidget.h"
#include "CoreMinimal.h"
#include "Public/AbstractCrafter.h"
#include "Public/StaticItem.h"

#include <Dom/JsonObject.h>

#include "SelectCrafter.generated.h"
class AMainPlayerController;
class UInventoryContainer;
class UCoreAccessor;

UENUM(BlueprintType)
enum class ECanAccomodate : uint8 {
  Unknown,
  Yes,
  No
};

UCLASS(BlueprintType)
/**
 * 
 */
class EVOSPACE_API USelectCrafter : public UAbstractCrafter {
  using Self = USelectCrafter;
  GENERATED_BODY()

  public:
  USelectCrafter();

  virtual void SelectRecipe(APlayerController *pc, int32 i) override;

  void RecipeSelectionPostprocess(APlayerController *pc);

  virtual void FindRecipe(APlayerController *pc, const UStaticItem *item) override;

  virtual void ResetRecipe() override;

  virtual void SaveSettings(TSharedPtr<FJsonObject> json,
                            AMainPlayerController *mpc = nullptr) override;
  virtual void LoadSettings(TSharedPtr<FJsonObject> json,
                            AMainPlayerController *mpc = nullptr) override;

  virtual void ReplaceWith(UBlockLogic *other) override;

  protected:
  virtual void Tick() override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float mCraftSpeedMultiplier = 1.0f;

  ECanAccomodate mCanAccomodate = ECanAccomodate::Unknown;

  virtual int32 GetSpeedLevel() const override;

  virtual void SetWorking(bool working);

  FBoolProperty *mWorking = nullptr;

  public:
  virtual void SetActor(ABlockActor *actor) override;

  virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UCoreAccessor *mAutoCrafterCoreAccessor;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventoryContainer *mAutoCrafterCoreInput;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventoryContainer *mAutoCrafterCoreOutput;

  EVO_LUA_CODEGEN_DB_EX(SelectCrafter);
  static void lua_reg(lua_State *L) {
    luabridge::getGlobalNamespace(L)
      .deriveClass<Self, UAbstractCrafter>("SelectCrafter")
      .endClass();
  }
};
