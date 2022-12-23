// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Blocks/BlockWidget.h"
#include "Evospace/Shared/Core/crafter_base.h"

#include <Dom/JsonObject.h>

#include "select_crafter.generated.h"

class AMainPlayerController;
class UInventoryContainer;
class UCoreAccessor;

UENUM(BlueprintType)
enum class ECanAccomodate : uint8 { Unknown, Yes, No };

UCLASS(BlueprintType)
class EVOSPACE_API USelectCrafter : public UCrafterBase {
    GENERATED_BODY()

    // Lua api
  public:
    /**
     * @brief Static function.
     * @param bl BlockLogic object
     * @return SelectCrafter object or nil
     */
    static USelectCrafter *cast(UBlockLogic *bl);

  public:
    USelectCrafter();

    void SpawnDropItems(APlayerController *pc);
    virtual void select_recipe(APlayerController *pc, int32 i) override;

    virtual void ResetRecipe() override;

    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;
    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

  protected:
    virtual void Tick() override;

    ECanAccomodate mCanAccomodate = ECanAccomodate::Unknown;

  protected:
    virtual int32 GetSpeedLevel() const override;

    virtual void SetWorking(bool working);
    FBoolProperty *mWorking = nullptr;

  public:
    virtual void SetActor(AActor *actor) override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

  public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UInventoryContainer *mAutoCrafterInputContainer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UInventoryContainer *mAutoCrafterOutputContainer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCoreAccessor *mAutoCrafterCoreAccessor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UInventoryContainer *mAutoCrafterCoreInput;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UInventoryContainer *mAutoCrafterCoreOutput;

  public:
    EVO_LUA_CODEGEN(USelectCrafter, SelectCrafter);
    static std::function<void(lua_State *)> GetRegisterLambda();
};
EVO_REGISTER_STATIC(USelectCrafter, SelectCrafter);
