// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Evospace/Common.h"
#include "UObject/Object.h"
#include "StaticModifier.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UStaticModifier : public UObject {
  GENERATED_BODY()

  public:
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UTexture2D *mImage;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FKeyTableObject mLabel;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FKeyTableObject mDescription;
};
