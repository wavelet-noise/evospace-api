// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Containers/Array.h"
#include "Core/tiered_block.h"
#include "CoreMinimal.h"
#include "Evospace/Blocks/Accessors/ConveyorInventorySideAccessor.h"
#include "Evospace/Blocks/ItemHopperInterface.h"

#include "conveyor.generated.h"

class UBaseAccessor;
class UInventory;
class UItemInventoryFilter;

UCLASS()
/**
 * @brief Vanilla conveyor BlockLogic
 */
class UConveyor : public UTieredBlock,
                  public ConveyorInterface,
                  public ISwitchInterface {
    GENERATED_BODY()

  public:
    UConveyor();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual Vec3i GetRotationLocks() const override;

    virtual void SetPushedSide(
        const Vec3i &side,
        UStaticIndexedItemHierarchicalInstancedStaticMeshComponent *comp =
            nullptr,
        int32 comp_index = INDEX_NONE
    ) override;

    virtual void OnSideAccessorAdded(UBaseAccessor &accessor) override;

    virtual void OnSideAccessorRemoved(UBaseAccessor &accessor) override;

    virtual void RemoveActor() override;

    void SetSwitched(bool val) override;
    bool GetSwitched() const override;

  protected:
    virtual void Tick() override;

    virtual void BlockBeginPlay() override;

    bool is_block_tick() const;

    void UpdateSides(UBaseAccessor *except);
    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;
    virtual void PostLoad() override;

    friend UConveyorInventorySideAccessor;

  protected:
    UPROPERTY(BlueprintReadOnly)
    UInventory *mInputInventory;

    UPROPERTY(BlueprintReadOnly)
    UInventory *mOutputInventory;

    UPROPERTY()
    int8 input_path = 0;

    UPROPERTY()
    bool mSwitched = true;

    UPROPERTY()
    int8 output_path = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int mSides = 0;

    ADimension *mDim;

    void SetActor(AActor *actor);

    UPROPERTY()
    USolidOutputAccessor *mOutputAccessor;

    UPROPERTY()
    TArray<UConveyorInventorySideAccessor *> mAllSides;

    UPROPERTY()
    UStaticIndexedItemHierarchicalInstancedStaticMeshComponent *mComp;

    int32 mCompIndex = INDEX_NONE;

    UPROPERTY()
    UStaticIndexedItemHierarchicalInstancedStaticMeshComponent *mComp2;

    int32 mComp2Index = INDEX_NONE;

  public:
    EVO_LUA_CODEGEN_DB_EX(Conveyor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla splitter BlockLogic
 */
class USplitter : public UTieredBlock {
    GENERATED_BODY()

  public:
    USplitter();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual Vec3i GetRotationLocks() const override;

    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;
    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    virtual void RemoveActor() override;

  protected:
    virtual void Tick() override;

    virtual void BlockBeginPlay() override;

    virtual bool is_block_tick() const override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;
    virtual void PostLoad() override;

  protected:
    UPROPERTY(BlueprintReadOnly)
    UInventory *mOutputInventory;

    ADimension *mDim;

    UPROPERTY(BlueprintReadOnly)
    UInventory *mInputInventory;

    UPROPERTY()
    int8 input_path = 0;

    UPROPERTY()
    int8 output_path = 0;

    UPROPERTY(BlueprintReadOnly)
    TArray<int32> mOutK;

    UFUNCTION(BlueprintCallable)
    void SetOutK(int32 index, int32 value);

    int32 mLastOut = 0;
    int32 mLastOuted = 0;

    virtual void SetInputPath(int8 item);
    virtual void SetOutputPath(int8 item);

    FObjectProperty *mInputItem = nullptr;
    const UItem *mLastInputItem = nullptr;
    FObjectProperty *mOutputItem = nullptr;
    const UItem *mLastOutputItem = nullptr;
    UByteProperty *mOutputIndex = nullptr;

    virtual void SetActor(AActor *actor) override;

    UPROPERTY()
    USolidInputAccessor *mInputAccessor;

    UPROPERTY()
    TArray<USolidOutputAccessor *> mAllSides;

  public:
    EVO_LUA_CODEGEN_DB_EX(Splitter);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla sorter BlockLogic
 */
class USorter : public USplitter {
    GENERATED_BODY()

  public:
    USorter();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    UPROPERTY(BlueprintReadOnly)
    TArray<UInventory *> mFilterInvs;

    UPROPERTY()
    UItemInventoryFilter *mFilter;

    UFUNCTION(BlueprintCallable)
    void PushFilter(UItem *item, int32 index);

    UFUNCTION(BlueprintCallable)
    void PopFilter(int32 index);

  protected:
    virtual void Tick() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(Sorter);
    static void lua_reg(lua_State *L);
};