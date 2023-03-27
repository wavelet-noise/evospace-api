// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/block_logic.h"
#include "CoreMinimal.h"

#include "tiered_block.generated.h"

UCLASS(BlueprintType)
/**
 * @brief Vanilla tiered block proto BlockLogic
 */
class UTieredBlock : public UBlockLogic {
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    /**
     * @brief tier of block ( 0 - stone, 1 - copper, 2 - steel, 3 - aluminium, 4
     * - stainless steel, 5 - titanium, 6 - hard metal, 7 - neutronium )
     */
    int32 tier = 0;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    /**
     * @brief level of block
     */
    int32 level = 0;

  public:
    UTieredBlock();

    virtual void SetActor(AActor *actor) override;

  public:
    EVO_LUA_CODEGEN_DB_EX(TieredBlock);
    static void lua_reg(lua_State *L);
};

UCLASS(BlueprintType)
/**
 * @brief Vanilla filtering block proto BlockLogic
 */
class UFilteringBlock : public UTieredBlock {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable)
    virtual void ChangeFilter(int32 inventory, int32 slot, UItem *item) {}

  public:
    EVO_LUA_CODEGEN_DB_EX(FilteringBlock);
    static void lua_reg(lua_State *L);
};
