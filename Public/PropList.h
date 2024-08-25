// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "../SerializableJson.h"

#include "PropList.generated.h"

class UStaticProp;
class UStaticAttach;

USTRUCT()
struct FPropListData {
  GENERATED_BODY()

  public:
  UPROPERTY()
  TArray<UStaticAttach *> Props;

  UPROPERTY()
  float Chance = 1.0;
};

UCLASS()
class UPropList : public UObject, public ISerializableJson {
  GENERATED_BODY()

  public:
  UPROPERTY()
  TArray<FPropListData> PropListDatas;

  UStaticAttach *PickOne(const FVector &start_point);

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  // int32 CullStart = 6000;
  // int32 CullEnd = 8000;
};