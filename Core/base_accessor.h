// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/prototype.h"
#include "CoreMinimal.h"
#include "accessor_proxy.h"

#include "base_accessor.generated.h"

UCLASS()
class UBaseAccessor : public UPrototype, public ISerializableJson {
    GENERATED_BODY()

    // Lua api
  public:
    // Legacy
    void SetSidePos(const Vec3i &side, const Vec3i &pos);

    virtual bool is_connectable(UBaseAccessor &other) const;

    UPROPERTY()
    /**
     * @brief Relative offset from (0,0,0) block for this accessor
     */
    FVector3i pos;

    UPROPERTY()
    /**
     * @brief Relative side of cube to interact with this accessor
     */
    FVector3i side;

    UPROPERTY()
    /**
     * @brief Absolute offset from (0,0,0) block for this accessor
     */
    FVector3i world_pos;

    UPROPERTY()
    /**
     * @brief Absolute side of cube to interact with this accessor
     */
    FVector3i world_side;

    UPROPERTY()
    // connected opposite accessor
    UBaseAccessor *opposite;

    /**
     * @brief Readonly property. Does this accessor can tick
     * @return
     */
    virtual bool is_active() const { return false; }

  public:
    UBaseAccessor();

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

  public:
    virtual void TickComponent();

    virtual void CacheWorldPos();

  public:
    EVO_LUA_CODEGEN_DB(UBaseAccessor, BaseAccessor);
    static void lua_reg(lua_State *L);
};
