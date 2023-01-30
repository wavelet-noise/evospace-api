// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once
#include "../../Item/SingleSlotInventory.h"
#include "../BlockWidget.h"
#include "CoreMinimal.h"
#include "Evospace/Shared/Vanilla/tiered_block.h"

#include "LedLogic.generated.h"

UCLASS()
/**
 * @brief Vanilla led BlockLogic
 */
class ULedLogic : public UTieredBlock {
    GENERATED_BODY()

  public:
    ULedLogic();

    USingleSlotInventory *inv;

    virtual void Tick() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 led_level = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor mColor = FLinearColor::White;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;
};
