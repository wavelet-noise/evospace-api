// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/select_crafter.h"
#include "CoreMinimal.h"

#include "hand_generator.generated.h"

class UKineticOutputAccessor;
class USingleSlotInventory;

UCLASS()
/**
 * @brief Hand powered generator
 */
class UHandGenerator : public UTieredBlock {
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Kinetic energy per click
     */
    int32 per_click = 10000;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Kinetic energy output per tick
     */
    int32 power = 10;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Kinetic energy stored
     */
    int32 stored = 0;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Kinetic energy stored
     */
    int32 max_stored = 100000;

  public:
    UHandGenerator();

    UPROPERTY()
    USingleSlotInventory *inventory;

    UPROPERTY()
    UKineticOutputAccessor *accessor;

    virtual bool is_block_tick() const override;

    UFUNCTION(BlueprintCallable)
    void OnGeneratorPressed();

    virtual void OnAction(
        const FHitResult &hit, const Vec3i &side, AItemLogicActor *item
    ) override;

  protected:
    virtual void Tick() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(HandGenerator);
    static void lua_reg(lua_State *L);
};