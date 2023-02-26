// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Vanilla/tiered_block.h"

#include "storage_block.generated.h"

UCLASS()
/**
 * @brief Vanilla storage block proto BlockLogic
 */
class UStorageBlock : public UTieredBlock {
    GENERATED_BODY()

  public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    UInventoryAccess *mStorageAccess;

    UFUNCTION(BlueprintCallable)
    virtual int64 GetCapacity() const;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

  public:
    EVO_LUA_CODEGEN_DB_EX(StorageBlock);
    static void lua_reg(lua_State *L);
};