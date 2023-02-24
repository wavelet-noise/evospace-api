// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Vanilla/tiered_block.h"

#include "pump.generated.h"

class USingleSlotInventory;
class UInventoryWhiteFilter;

UCLASS()
/**
 * @brief Vanilla pump BlockLogic
 */
class UPump : public UTieredBlock {
    GENERATED_BODY()

  public:
    UPump();

    virtual bool is_block_tick() const override;

    virtual void Tick() override;

    bool TakeInventory();
    bool GiveInventory();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    void UpdateSides(UBlockLogic *except = nullptr);
    virtual void SetActor(AActor *actor) override;
    virtual void
    OnNeighborBlockAdded(UBlockLogic *neighbour, const Vec3i &pos) override;
    virtual void
    OnNeighborBlockRemoved(UBlockLogic *neighbour, const Vec3i &pos) override;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    bool mRight = false;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    bool mLeft = false;

  protected:
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    USingleSlotInventory *mFluidInventory;

  private:
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    int a_progress;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    bool mWaterFound = false;

  public:
    EVO_LUA_CODEGEN_DB(UPump, Pump);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla diode BlockLogic
 */
class UDiode : public UTieredBlock {
    GENERATED_BODY()

  public:
    UDiode();

    virtual bool is_block_tick() const override;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    USingleSlotInventory *mFluidInventory;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

  public:
    EVO_LUA_CODEGEN_DB(UDiode, Diode);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla filtering pump BlockLogic
 */
class UFilteringPump : public UPump {
    GENERATED_BODY()

  public:
    UFilteringPump();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    UFUNCTION(BlueprintCallable)
    void SetFilter(UItem *i);

    UFUNCTION(BlueprintCallable)
    TArray<UItem *> GetItems() const;

    UPROPERTY()
    UInventoryWhiteFilter *mWhiteFilter;

    UPROPERTY(BlueprintReadOnly)
    UItem *mSelectedItem = nullptr;

    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

  public:
    EVO_LUA_CODEGEN_DB(UFilteringPump, FilteringPump);
    static void RegisterLua(lua_State *L);
};