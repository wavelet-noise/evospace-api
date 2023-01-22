// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Evospace/Blocks/ItemHopperInterface.h"
#include "Evospace/Shared/Core/select_crafter.h"

#include "auto_crafter.generated.h"

class UInternalInventory;
class UInventory;

UCLASS(BlueprintType)
class UAutoCrafter : public USelectCrafter {
    GENERATED_BODY()

    // Lua api
  public:
    // TODO: remake this with lua for inventory
    // AutoCrafterOutputContainer slot force capacity
    int32 force_capacity = 0;

  protected:
    UAutoCrafter();

    virtual void Tick() override;

    UPROPERTY()
    UInternalInventory *mLastInventory;

  public:
    virtual bool is_universal_crafter() const override;

    virtual void select_recipe(APlayerController *pc, int32 i) override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  public:
    EVO_LUA_CODEGEN_DB(UAutoCrafter, AutoCrafter);
    static void RegisterLua(lua_State *L);
};

UCLASS(BlueprintType)
class UDeconstructorCrafterBlockLogic : public UAutoCrafter {
    GENERATED_BODY()

  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
};

UCLASS(BlueprintType)
class UDumpAnyBlockLogic : public UTieredBlock, public ISwitchInterface {
    GENERATED_BODY()

  public:
    UDumpAnyBlockLogic();

    virtual void Tick() override;

    virtual bool is_block_tick() const override;

    virtual void BlockBeginPlay() override;

    void SetActor(AActor *actor);
    FObjectProperty *mItem = nullptr;

    virtual void SetWorking(bool working);
    FBoolProperty *mWorking = nullptr;

    void SetSwitched(bool val) override;

    bool GetSwitched() const override;

  protected:
    UPROPERTY()
    UInventory *mInputInventory;

    bool mSwitchedOn = true;

    int32 AnimationTicks = 0;

  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;
};

UCLASS(BlueprintType)
class UDumpCrafterBlockLogic : public USelectCrafter {
    GENERATED_BODY()

  protected:
    virtual void Tick() override;

    virtual void BlockBeginPlay() override;

    void SetActor(AActor *actor);
    FObjectProperty *mItem = nullptr;

  public:
    virtual bool is_universal_crafter() const override;

    virtual void select_recipe(APlayerController *pc, int32 i) override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    int32 AnimationTicks = 0;
};