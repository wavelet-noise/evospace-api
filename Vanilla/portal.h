// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FissionReactorBlockLogic.h"

#include "Portal.generated.h"

UCLASS()
/**
 * @brief Vanilla portal BlockLogic
 */
class UPortal : public UFusionReactor {
    GENERATED_BODY()

  public:
    UPortal();

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    bool mPinging;

  protected:
    void Tick() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(Portal);
    static void RegisterLua(lua_State *L);
};