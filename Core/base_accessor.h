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

    /**
     * @brief offset from (0,0,0) block for this accessor
     */
    Vec3i pos;

    /**
     * @brief side of cube to interact with this accessor
     */
    Vec3i side;

    std::optional<evo::AccessorListener> opposite;

  public:
    UBaseAccessor();

    UBaseAccessor *GetOutsideAccessor(UClass *type);

    const UBaseAccessor *GetOutsideAccessor(UClass *type) const;

    UBaseAccessor *GetOutsideAccessor() {
        return GetOutsideAccessor(GetClass());
    }

    const UBaseAccessor *GetOutsideAccessor() const {
        return GetOutsideAccessor(GetClass());
    }

    template <class T> T *GetOutsideAccessor() {
        return static_cast<T *>(GetOutsideAccessor(T::StaticClass()));
    }

    template <class T> const T *GetOutsideAccessor() const {
        return static_cast<const T *>(GetOutsideAccessor(T::StaticClass()));
    }

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool test_outside(UBaseAccessor * acc) const;

  public:
    virtual void TickComponent();

  protected:
    virtual void BeginPlay();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

  public:
    EVO_LUA_CODEGEN_DB(UBaseAccessor, BaseAccessor);
    static void lua_reg(lua_State *L);
};
