// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/Blocks/ItemHopperInterface.h"
#include "Evospace/Blocks/TieredBlockLogic.h"
#include "CoreMinimal.h"

#include "crafter_base.generated.h"

class UInternalInventory;

UCLASS(BlueprintType)
class EVOSPACE_API UCrafterBase : public UTieredBlockLogic,
                                  public ISwitchInterface {
    GENERATED_BODY()

    // Lua api
  public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /**
     * @brief Property. Crafter will make recipe if output slot is already full
     */
    bool load_independent = false;

    UFUNCTION(BlueprintCallable)
    /**
     * @brief Readonly property.
     */
    virtual bool is_busy() const;

    UFUNCTION(BlueprintCallable)
    /**
     * @brief Readonly property.
     */
    virtual bool is_output_error() const;

    UFUNCTION(BlueprintCallable)
    /**
     * @brief Readonly property.
     */
    virtual bool is_input_error() const;

    /**
     * @brief Readonly property.
     */
    virtual bool is_block_tick() const override;

    UFUNCTION(BlueprintCallable)
    /**
     * @brief Readonly property.
     */
    virtual bool is_universal_crafter() const;

    // Engine code
  public:
    UCrafterBase();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    UFUNCTION(BlueprintCallable)
    virtual const URecipeDictionary *GetRecipeDictionary() const;

    UFUNCTION(BlueprintCallable)
    virtual const URecipe *GetCurrentRecipe() const;

    UFUNCTION(BlueprintCallable)
    virtual void SelectRecipe(APlayerController *pc, int32 i);

    UFUNCTION(BlueprintCallable)
    virtual void ResetRecipe();

    UFUNCTION(BlueprintCallable)
    virtual float GetCurrentProgress() const;

    UFUNCTION(BlueprintCallable)
    virtual int32 GetSpeedLevel() const;

    UFUNCTION(BlueprintCallable)
    virtual int32 GetRecipeTicks(int32 &plevel) const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 ticks_passed = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 real_ticks_passed = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 input_ticks = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 output_ticks = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 to_loss = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int64 output_excess = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int64 input_to_get = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UInternalInventory *mRecipeListTierHelper = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool input_gathered = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mSwitchedOn = true;

    void SetSwitched(bool val) override;
    bool GetSwitched() const override;

  protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintCosmetic)
    void SetWorkingState(float efficiency);

    UFUNCTION(BlueprintCallable)
    virtual UInventoryReader *GetBusy() const;

    static UCrafterBase *cast(UBlockLogic *bl);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mBusy = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mResOutputError = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mResInputError = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mPowerLevelError = false;

  protected:
    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    const URecipeDictionary *mRecipeDictionary;

    friend class UBlockModdingLuaState;

    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    const URecipe *mCurrentRecipe = nullptr;

  public:
    EVO_LUA_CODEGEN(UCrafterBase);
    static std::function<void(lua_State *)> GetRegisterLambda();
};
EVO_REGISTER_STATIC(UCrafterBase, CrafterBase);
