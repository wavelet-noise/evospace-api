// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Vanilla/tiered_block.h"

#include "drilling_rig.generated.h"


class UOreSector;class UBoolProperty;
class UItem;
class USingleSlotInventory;
class UKineticInputAccessor;
class UBaseInventoryAccessor;

UCLASS()
/**
 * @brief Vanilla miner proto BlockLogic
 */
class UMinerBase : public UTieredBlock {
    GENERATED_BODY()

  public:
    virtual bool is_block_tick() const override;

    virtual void BlockBeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    USingleSlotInventory *mOutputInventory;

    UPROPERTY(BlueprintReadOnly)
    USingleSlotInventory *mPowerInventory;

    UPROPERTY(BlueprintReadOnly)
    int32 mTicksToGet = 0;

    UPROPERTY(BlueprintReadOnly)
    int32 mTicksMax = 1;

    UPROPERTY(BlueprintReadOnly)
    int32 mSupply = std::numeric_limits<int32>::max();

    UPROPERTY(BlueprintReadOnly)
    int32 mSupplyTemp = 1;

    UPROPERTY(BlueprintReadOnly)
    UItem *mDiggingItem = nullptr;

    UPROPERTY()
    UOreSector * ore_sector = nullptr;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    UFUNCTION(BlueprintCallable)
    void SelectItem(UItem *item);

    UOreSector * get_ore_sector() const;

    virtual bool CheckItem(const UItem *i) const;

    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

  protected:
    virtual void Tick() override;

    virtual void SetWorking(bool working);

    virtual void SetActor(AActor *actor) override;

    UPROPERTY()
    UBaseInventoryAccessor *mOutput = nullptr;

    UPROPERTY()
    UKineticInputAccessor *mPower = nullptr;

    UPROPERTY()
    bool mWorking = false;

  private:
    ADimension *dim = nullptr;

  public:
    EVO_LUA_CODEGEN_DB_EX(MinerBase);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla drilling rig BlockLogic
 */
class UDrillingRig : public UMinerBase {
    GENERATED_BODY()

  public:
    UDrillingRig();

    virtual bool CheckItem(const UItem *i) const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(DrillingRig);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla pumpjack BlockLogic
 */
class UPumpjack : public UMinerBase {
    GENERATED_BODY()

  public:
    UPumpjack();

    virtual bool CheckItem(const UItem *i) const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(Pumpjack);
    static void lua_reg(lua_State *L);
};
