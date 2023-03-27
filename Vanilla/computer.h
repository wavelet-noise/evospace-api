// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/tiered_block.h"
#include "CoreMinimal.h"

#include "computer.generated.h"

class UByteProperty;
class USingleSlotInventory;
class UInventoryContainer;
class UCoreAccessor;
class UElectricInputAccessor;

UCLASS()
/**
 * @brief Vanilla computer BlockLogic
 */
class UComputer : public UTieredBlock {
    GENERATED_BODY()

  public:
    UComputer();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UInventoryContainer *chip_container;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USingleSlotInventory *electric_invenvory;

    FByteProperty *mStatusProperty = nullptr;
    FByteProperty *mLastTierProperty = nullptr;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual bool is_block_tick() const override;

    int8 TicksToGet = 20;
    int8 mStatus = 0;
    int8 mLastTier = 0;

    virtual void SetStatus(int8 w);
    virtual void SetLastTier(int8 w);

    virtual void SetActor(AActor *actor) override;

  protected:
    virtual void Tick() override;

    UPROPERTY()
    UElectricInputAccessor *electric_input;

    UPROPERTY()
    TArray<USingleSlotInventory *> chip_inventory;

    UPROPERTY()
    UCoreAccessor *core_accessor;

    virtual void lua_postprocess(ModLoadingContext &context) override;

  public:
    EVO_LUA_CODEGEN_DB_EX(Computer);
    static void lua_reg(lua_State *L);
};

UCLASS()
class UQuantumComputer : public UComputer {
    GENERATED_BODY()

  public:
    UQuantumComputer();

  protected:
    virtual void Tick() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(QuantumComputer);
    static void lua_reg(lua_State *L);
};