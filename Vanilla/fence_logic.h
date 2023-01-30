// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "../../Blocks/SidesArray.h"
#include "../../CoordinateMinimal.h"
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/block_logic.h"
#include "Evospace/Shared/Vanilla/tiered_block.h"

#include <Engine/EngineTypes.h>

#include "fence_logic.generated.h"

class AItemLogicActor;

UCLASS()
/**
 * @brief Vanilla fence BlockLogic
 */
class UFenceLogic : public UBlockLogic {
    GENERATED_BODY()

  public:
    UFenceLogic();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual void OnNeighborBlockAdded(UBlockLogic *block, const Vec3i &pos);
    virtual void OnNeighborBlockRemoved(UBlockLogic *block, const Vec3i &pos);

    virtual Vec3i GetRotationLocks() const override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int mSides = 0;

    virtual void SetActor(AActor *actor) override;

    virtual void RemoveActor() override;

  protected:
    void UpdateSides(UBlockLogic *except = nullptr);

  public:
    EVO_LUA_CODEGEN_DB_EX(FenceLogic);
    static void RegisterLua(lua_State *L);
};

UCLASS()
class UDoorLogic : public UBlockLogic {
    GENERATED_BODY()

  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    void
    OnAction(const FHitResult &hit, const Vec3i &side, AItemLogicActor *item);

    UPROPERTY(BlueprintReadOnly)
    bool mOpened = false;

    virtual void SetActor(AActor *actor) override;

  public:
    EVO_LUA_CODEGEN_DB_EX(DoorLogic);
    static void RegisterLua(lua_State *L);
};

UCLASS()
class ULampLogic : public UTieredBlock {
    GENERATED_BODY()

  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    void
    OnAction(const FHitResult &hit, const Vec3i &side, AItemLogicActor *item);

    UPROPERTY(BlueprintReadOnly)
    int32 mType = false;

    virtual void SetActor(AActor *actor) override;

  public:
    EVO_LUA_CODEGEN_DB_EX(LampLogic);
    static void RegisterLua(lua_State *L);
};

UCLASS()
class UBedLogic : public UBlockLogic {
    GENERATED_BODY()

  public:
    void
    OnAction(const FHitResult &hit, const Vec3i &side, AItemLogicActor *item);

  public:
    EVO_LUA_CODEGEN_DB_EX(BedLogic);
    static void RegisterLua(lua_State *L);
};
