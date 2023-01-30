// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/select_crafter.h"

#include "FissionReactorBlockLogic.generated.h"

UCLASS()
/**
 * @brief Fission reactor crafter
 */
class UFissionReactor : public USelectCrafter {
    GENERATED_BODY()

  public:
    UFissionReactor();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    void AwakeReactorAnimation();

    int64 mCurrentHeat = 0;
    int64 mHeatCapacity = 10000;
    int64 mStorageDrain = 10;

    virtual void SetActor(AActor *actor) override;

    FInt64Property *mHeatCapacityProperty;
    FInt64Property *mCurrentHeatProperty;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

  protected:
    virtual void Tick() override;

  public:
    EVO_LUA_CODEGEN_DB(UFissionReactor, FissionReactor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Fusion reactor crafter
 */
class UFusionReactor : public USelectCrafter {
    GENERATED_BODY()

  public:
    virtual void Tick() override;

  public:
    EVO_LUA_CODEGEN_EMPTY(UFusionReactor, USelectCrafter, FusionReactor);
};