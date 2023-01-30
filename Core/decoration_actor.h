// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"

#include "decoration_actor.generated.h"

class UStaticDecoration;

UCLASS()
/**
 * @brief World decoration actor
 */
class ADecorationActor : public AActor {
    GENERATED_BODY()
  public:
    const UStaticDecoration *GetStaticDecoration() const;
    void SetStaticDecoration(const UStaticDecoration *static_decoration);

  protected:
    UPROPERTY()
    const UStaticDecoration *mStaticDecoration;
};
