// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/CoordinateMinimal.h"
#include "../BlockWidget.h"
#include "../ItemHopperInterface.h"
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/item.h"
#include "Evospace/Shared/Vanilla/inventory.h"
#include "Evospace/Shared/Vanilla/tiered_block.h"

#include "robot_arm.generated.h"

UCLASS()
/**
 * @brief Vanilla robot arm BlockLogic
 */
class URobotArm : public UTieredBlock, public ISwitchInterface {
    GENERATED_BODY()

  public:
    URobotArm();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual void BlockBeginPlay() override;
    virtual void Tick() override;

    virtual bool is_block_tick() const override;
    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    void SetSwitched(bool val) override;

    bool GetSwitched() const override;

  protected:
    virtual bool TakeInventory();
    bool GiveInventory();

    enum animation {
        a_pick,
        a_drop

    } a_status;

    int32 a_progress;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UInventory *mInventory;

    virtual void SetPickedItem(UItem *item);
    virtual void SetDirection(int32 dir, int32 predir);
    FObjectProperty *mPickedItem = nullptr;
    FIntProperty *mDirection = nullptr;
    FIntProperty *mPreDirection = nullptr;
    void SetActor(AActor *actor);

    UPROPERTY(EditAnywhere)
    int64 mItemPortion = 1ll;

    bool mSwitched = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 mRightDir = cs::SideToIndex(Side::Right);

  public:
    EVO_LUA_CODEGEN_DB_EX(RobotArm);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla filtering robot arm BlockLogic
 */
class UFilteringRobotArm : public URobotArm {
    GENERATED_BODY()

  public:
    UFilteringRobotArm();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UInventory *mFilter;

  public:
    EVO_LUA_CODEGEN_DB_EX(FilteringRobotArm);
    static void RegisterLua(lua_State *L);
};