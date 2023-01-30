
// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Shared/Core/entity.h"

#include <string>

#include "static_attach.generated.h"

class ASector;

UCLASS(Abstract)
/**
 * @brief World decoration object
 */
class UStaticAttach : public UEntity {
    GENERATED_BODY()

  public:
    std::string name;

    virtual bool Create(
        ASector *sector, const FTransform &transform, bool ignored = false
    ) const {
        return false;
    };

  public:
    EVO_LUA_CODEGEN_DB(UStaticAttach, StaticAttach);
    static void RegisterLua(lua_State *L);
};
