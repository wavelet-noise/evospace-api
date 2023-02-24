// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Blocks/ItemHopperInterface.h"
#include "Evospace/Common.h"
#include "Vanilla/storage_block.h"

#include "Conductor.generated.h"

class UConductor;
class UBaseInventoryAccessor;
class UGraphStorage;
class USingleSlotInventory;
class UBlockLogic;
class UBaseAccessor;
class AItemLogicActor;

UCLASS(BlueprintType)
class UBlockNetwork : public UObject {
    GENERATED_BODY()

  public:
    UBlockNetwork();

    bool AddBlock(UConductor *a);
    bool RemoveBlock(UConductor *a);

    void PrepareToLogicSave();
    bool AddInputAccessor(UBaseInventoryAccessor *accessor);
    bool AddOutputAccessor(UBaseInventoryAccessor *accessor);

    bool RemoveInputAccessor(UBaseInventoryAccessor *accessor);
    bool RemoveOutputAccessor(UBaseInventoryAccessor *accessor);

    bool IsEmpty() const;

    static TSet<UConductor *> CheckIntegrity(UConductor *block);
    static bool _CheckIntegrity(
        UConductor *block, TArray<Vec3i> &queue, TArray<Vec3i> &queue_from,
        TSet<UConductor *> &visited
    );

    void DeferredKill(int64 rem_capacity = 0, bool no_prepare = false);

    bool IsKillDeferred() const { return mKillDeferred; }

    void SetResource(const UItem *param1);

  protected:
    UPROPERTY(VisibleAnywhere)
    TArray<UConductor *> mWires;

    UPROPERTY(VisibleAnywhere)
    TArray<UConductor *> mStorages;

    UPROPERTY(VisibleAnywhere)
    TArray<UBaseInventoryAccessor *> mInputs;

    UPROPERTY(VisibleAnywhere)
    TArray<UBaseInventoryAccessor *> mOutputs;

    UPROPERTY(VisibleAnywhere)
    TArray<USwitch *> mSwitches;

  public:
    UPROPERTY(VisibleAnywhere)
    bool mIsDataNetwork = false;

    void Tick();

    template <typename _Ty, typename Ty2_>
    void RotateArray(TArray<TPair<_Ty *, Ty2_ *>> &c) {
        auto coll_copy = c;
        auto shift = rand();
        for (int i = 0; i < coll_copy.Num(); ++i) {
            auto new_i = i + shift % coll_copy.Num();
            if (new_i >= coll_copy.Num())
                new_i -= coll_copy.Num();

            c[new_i] = coll_copy[i];
        }
    }

    UFUNCTION(BlueprintCallable)
    const UItem *GetResource() const;

    UFUNCTION(BlueprintCallable)
    float GetCharge() const;

    UFUNCTION(BlueprintCallable)
    float GetCapacity() const;

    int64 GetCharge64() const;
    int64 GetCapacity64() const;

    UFUNCTION(BlueprintCallable)
    float GetTotalDrain() const;

    UFUNCTION(BlueprintCallable)
    bool AddCharge(int64 addition);

    UFUNCTION()
    void EndTick();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UGraphStorage *mConsumptionStorage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UGraphStorage *mProductionStorage;

    int64 mPerWireCon;

    TSet<UBlockNetwork *> CollectedNetworks;

    void ClearCollectedDirty();

    bool mCollectedDirty = true;

  private:
    const UItem *mResource = nullptr;

    bool mKillDeferred = false;

    int32 mLifetime = 0;

    bool mUpdated = false;

    int64 mCapacity = 0;
    int64 mCharge = 0;

    UPROPERTY()
    USingleSlotInventory *mDrainInventory;

    UPROPERTY()
    UBaseInventoryAccessor *mDrainAccessor;

    TArray<TPair<const UItem *, UInventoryAccess *>> CollectedOutputs;
    TArray<TPair<const UItem *, UInventoryAccess *>> CollectedInputs;
    TArray<TPair<const UItem *, UInventoryAccess *>> CollectedStorages;
};

/// Conductors

UCLASS(Abstract)
/**
 * @brief Vanilla conductor proto BlockLogic
 */
class UConductor : public UStorageBlock {
    GENERATED_BODY()

  public:
    virtual void
    OnNeighborBlockAdded(UBlockLogic *neighbour, const Vec3i &pos) override;
    virtual void
    OnNeighborBlockRemoved(UBlockLogic *neighbour, const Vec3i &pos) override;

    virtual int64 GetCapacity() const override;
    virtual int64 GetCharge() const;

    virtual Vec3i GetRotationLocks() const override;

    virtual UClass *GetInputAccClass() const { return nullptr; }

    virtual UClass *GetOutputAccClass() const { return nullptr; }

    virtual UClass *GetConductorAccClass() const { return nullptr; }

    virtual UClass *GetSwitchBlockClass() const { return nullptr; }

    virtual UClass *GetConductorBlockClass() const { return nullptr; }

    UFUNCTION(BlueprintCallable)
    virtual int64 GetPerWire() const { return 0; }

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual const TArray<Vec3i> &GetConductionSides() const;

    bool SetChannel(int32 channel);
    virtual int32 GetChannel() const;

    virtual EBlockWidgetType GetWidgetType() const override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int mSides = 0;

    virtual bool CheckPlaceble(ADimension *dim, FVector3i pos) const override;

  protected:
    virtual void BlockBeginPlay() override;

    virtual void RebuildFrom(int64 rem_capacity = 0);

    virtual void BlockEndPlay() override;

  protected:
    // ReSharper disable once CppUE4ProbableMemoryIssuesWithUObjectsInContainer
    TArray<UBaseAccessor *> mWireAccessor;

    virtual void UpdateSides(UBaseAccessor *except = nullptr);

    //==================================================================
  public:
    friend UBlockNetwork;
    friend USwitch;

    virtual bool Connect(UConductor *block);

    virtual bool Disconnect(UConductor *block);

    virtual bool IsDataNetwork() const;

    UFUNCTION(BlueprintCallable)
    UBlockNetwork *GetNetwork() const;

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UBlockNetwork *mNetwork = nullptr;

    int32 mChannel = 0;

  public:
    EVO_LUA_CODEGEN_DB_EX(Conductor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid conductor BlockLogic
 */
class UFluidConductor : public UConductor {
    GENERATED_BODY()
  public:
    UFluidConductor();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidConductor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla electric conductor BlockLogic
 */
class UElectricConductor : public UConductor {
    GENERATED_BODY()
  public:
    UElectricConductor();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricConductor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data conductor BlockLogic
 */
class UDataConductor : public UConductor {
    GENERATED_BODY()
  public:
    UDataConductor();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    bool IsDataNetwork() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(DataConductor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat conductor BlockLogic
 */
class UHeatConductor : public UConductor {
    GENERATED_BODY()
  public:
    UHeatConductor();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;
    virtual int64 GetPerWire() const override;

    virtual int64 GetCapacity() const override;

    virtual bool is_block_tick() const override;
    USingleSlotInventory *mStorage;

    UPROPERTY(EditAnywhere)
    float mBaseCapacity = 1.f;

    UPROPERTY(EditAnywhere)
    float mBonusCapacity = 1.f;

    virtual void BlockBeginPlay() override;

    virtual int64 GetCharge() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatConductor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic conductor BlockLogic
 */
class UKineticConductor : public UConductor {
    GENERATED_BODY()

  public:
    UKineticConductor();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;
    virtual int64 GetPerWire() const override;

    virtual int64 GetCapacity() const override;

    virtual bool is_block_tick() const override;
    USingleSlotInventory *mStorage;

    UPROPERTY(
        EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")
    )
    float mBaseCapacity = 1.f;

    UPROPERTY(
        EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")
    )
    float mBonusCapacity = 1.f;

    bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    int64 GetCharge() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticConductor);
    static void RegisterLua(lua_State *L);
};

/// Switches

UCLASS()
/**
 * @brief Vanilla switch proto BlockLogic
 */
class USwitch : public UConductor, public ISwitchInterface {
    GENERATED_BODY()

  public:
    void RebuildFrom(int64 rem_capacity = 0);
    virtual const TArray<Vec3i> &GetConductionSides() const override;
    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    virtual void OnAction(
        const FHitResult &hit, const Vec3i &side, AItemLogicActor *item
    ) override;

    bool IsSwithedOn() const;
    bool mSwitchedOn = false;

    virtual void SetActor(AActor *actor) override;

    virtual void UpdateSides(UBaseAccessor *except = nullptr) override;

    virtual bool is_block_tick() const override;

    virtual void
    OnNeighborBlockAdded(UBlockLogic *neighbour, const Vec3i &pos) override;

    virtual void
    OnNeighborBlockRemoved(UBlockLogic *neighbour, const Vec3i &pos) override;

    virtual void SetSwitched(bool val) override;

    virtual bool GetSwitched() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(Switch);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla electric switch BlockLogic
 */
class UElectricSwitch : public USwitch {
    GENERATED_BODY()
  public:
    UElectricSwitch();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;
    virtual int32 GetChannel() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricSwitch);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid switch BlockLogic
 */
class UFluidSwitch : public USwitch {
    GENERATED_BODY()
  public:
    UFluidSwitch();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;
    virtual int32 GetChannel() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidSwitch);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat switch BlockLogic
 */
class UHeatSwitch : public USwitch {
    GENERATED_BODY()
  public:
    UHeatSwitch();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;
    virtual int32 GetChannel() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatSwitch);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic switch BlockLogic
 */
class UKineticSwitch : public USwitch {
    GENERATED_BODY()
  public:
    UKineticSwitch();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;
    virtual int32 GetChannel() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticSwitch);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data switch BlockLogic
 */
class UDataSwitch : public USwitch {
    GENERATED_BODY()
  public:
    UDataSwitch();
    virtual UClass *GetInputAccClass() const override;
    virtual UClass *GetOutputAccClass() const override;
    virtual UClass *GetConductorAccClass() const override;
    virtual UClass *GetSwitchBlockClass() const override;
    virtual UClass *GetConductorBlockClass() const override;
    virtual int32 GetChannel() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(DataSwitch);
    static void RegisterLua(lua_State *L);
};