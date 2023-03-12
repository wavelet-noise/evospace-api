// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Vanilla/storage_block.h"

#include "item_rack.generated.h"

class USingleSlotInventory;
class AActor;

UCLASS()
/**
 * @brief Vanilla item rack BlockLogic
 */
class UItemRack : public UStorageBlock {
    GENERATED_BODY()

  public:
    UItemRack();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

  protected:
    UPROPERTY(
        EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")
    )
    USingleSlotInventory *mInventory;

    virtual int64 GetCapacity() const override;

  private:
    virtual void SetActor(AActor *actor) override;

    static const int32 mBaseSize = 2048;

  public:
    EVO_LUA_CODEGEN_DB_EX(ItemRack);
    static void lua_reg(lua_State *L);
};
