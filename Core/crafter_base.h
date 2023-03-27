// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/tiered_block.h"
#include "CoreMinimal.h"
#include "Evospace/Blocks/ItemHopperInterface.h"

#include "crafter_base.generated.h"

class UInternalInventory;
class URecipeDictionary;

UCLASS(Abstract, BlueprintType)
/**
 * @brief Abstract Class.
 */
class UCrafterBase : public UTieredBlock, public ISwitchInterface {
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

    /**
     * @brief Static function.
     * @param bl BlockLogic object
     * @return CrafterBase object or nil
     */
    static UCrafterBase *cast(UBlockLogic *bl);

    UFUNCTION(BlueprintCallable)
    /**
     * @brief Change selected recipe in this crafter
     * @param pc Who have changed recipe or nil
     * @param i recipe index to select
     */
    virtual void select_recipe(APlayerController *pc, int32 i);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    /**
     * @brief Property. RecipeDictionary linked with this crafter
     * @return RecipeDictionary object
     */
    const URecipeDictionary *recipe_dictionary;

    // Engine code
  public:
    UCrafterBase();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    std::vector<std::vector<uint16>> input_split;
    std::vector<std::vector<uint16>> output_split;

    virtual void EvospacePostDuplicate(const UBlockLogic *proto) override;

    virtual void lua_postprocess(ModLoadingContext &context) override;

    UFUNCTION(BlueprintCallable)
    virtual const URecipe *GetCurrentRecipe() const;

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mBusy = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mResOutputError = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mResInputError = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool mPowerLevelError = false;

  protected:
    friend class UBlockModdingLuaState;

    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    const URecipe *mCurrentRecipe = nullptr;

  public:
    EVO_LUA_CODEGEN_DB(UCrafterBase, CrafterBase);
    static void lua_reg(lua_State *L);
};
