// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/CoordinateMinimal.h"
#include "Vanilla/tiered_block.h"

#include "Monitor.generated.h"

UCLASS()
/**
 * @brief Vanilla monitor BlockLogic
 */
class UMonitor : public UTieredBlock {
    GENERATED_BODY()

  public:
    UMonitor();

    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc
    ) override;
    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc
    ) override;

    virtual void BlockBeginPlay() override;
    virtual void BlockEndPlay() override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual void SetActor(AActor *actor) override;

    virtual bool is_block_tick() const override;

  protected:
    virtual void
    OnNeighborBlockAdded(UBlockLogic *block, const Vec3i &pos) override;
    virtual void
    OnNeighborBlockRemoved(UBlockLogic *block, const Vec3i &pos) override;

  protected:
    virtual void Tick() override;

  private:
    UBlockLogic *GetBlock();

    Vec3i mDataPosition;
    Vec3i mDataSide;

    void SetLogic(UBlockLogic *logic);
    FObjectProperty *mLogicProperty;
    UBlockLogic *mLastLogic;

  protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FVector2D mOffset = {0, 0};

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float mScale = 1.f;

  public:
    EVO_LUA_CODEGEN_DB_EX(Monitor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla sign BlockLogic
 */
class USignBlock : public UTieredBlock {
    GENERATED_BODY()

  public:
    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc
    ) override;
    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc
    ) override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    FString mText;

  public:
    EVO_LUA_CODEGEN_DB_EX(SignBlock);
    static void RegisterLua(lua_State *L);
};