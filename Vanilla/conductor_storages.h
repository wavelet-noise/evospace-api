// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Vanilla/conductor.h"

#include "conductor_storages.generated.h"

class USingleSlotInventory;
class UBaseAccessor;

UCLASS()
/**
 * @brief Vanilla battery box BlockLogic
 */
class UBatteryBox : public UElectricConductor {
    GENERATED_BODY()

  public:
    UBatteryBox();
    UBatteryBox(float base, float bonus);

    virtual int64 GetCapacity() const override;

    virtual int64 GetCharge() const override;

    UPROPERTY(BlueprintReadOnly)
    USingleSlotInventory *mInventory;

  protected:
    int64 base_capacity = 1000000;
    int64 bonus_capacity = 1000000;

    virtual void UpdateSides(UBaseAccessor *except = nullptr) override;
    virtual int32 GetChannel() const override;
    virtual void BlockBeginPlay() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(BatteryBox);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid container BlockLogic
 */
class UFluidContainer : public UFluidConductor {
    GENERATED_BODY()

  public:
    UFluidContainer();

    virtual int64 GetCapacity() const override;
    virtual int64 GetCharge() const override;

    virtual void UpdateSides(UBaseAccessor *except = nullptr) override;

    virtual int32 GetChannel() const override;
    virtual void BlockBeginPlay() override;

  protected:
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    USingleSlotInventory *mInventory;

    int64 base_capacity = 30;
    int64 bonus_capacity = 30;

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidContainer);
    static void RegisterLua(lua_State *L);
};