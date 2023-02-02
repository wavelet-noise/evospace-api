// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/Shared/Vanilla/static_attach.h"

#include "static_decoration.generated.h"

UCLASS()
/**
 * @brief World decoration object
 */
class UStaticDecoration : public UStaticAttach {
    GENERATED_BODY()

  public:
    virtual bool Create(
        ASector *sector, const FTransform &transform, bool ignored = false
    ) const;
};
