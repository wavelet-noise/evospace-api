// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BlockActor.generated.h"

class UBlock;
class UBlockLogic;

UCLASS(BlueprintType)
/**
 * @brief Block actor base class
 */
class ABlockActor : public AActor {
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    ABlockActor();

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    UBlockLogic *block_logic;

    UFUNCTION(BlueprintNativeEvent)
    void ChangeBordersStatus(bool status);

    UPROPERTY()
    TArray<UStaticMeshComponent *> border_components;
};
