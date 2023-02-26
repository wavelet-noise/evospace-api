// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "storage_block.h"

#include "chest.generated.h"

class USolidAccessor;
class UCoreAccessor;
class UInventory;

UCLASS()
/**
 * @brief Vanilla chest BlockLogic
 */
class UChest : public UStorageBlock {
    GENERATED_BODY()

  public:
    UChest();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, BlueprintCosmetic)
    void SetOpenState(bool opened);

    UFUNCTION(BlueprintCallable)
    virtual void SetLimit(int32 _l);

    UFUNCTION(BlueprintCallable)
    virtual int32 GetLimit() const;

    virtual int64 GetCapacity() const override;

  protected:
    UPROPERTY(
        EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")
    )
    UInventory *mInventory;

    USolidAccessor *input_accessor[Side::NumSides];
    UCoreAccessor *mInputInventory;

  private:
    static const int32 mBaseSize = 20;

  public:
    EVO_LUA_CODEGEN_DB_EX(Chest);
    static void lua_reg(lua_State *L);
};
