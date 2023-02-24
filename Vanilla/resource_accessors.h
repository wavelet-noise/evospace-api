// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/base_inventory_accessor.h"
#include "Core/prototype.h"
#include "CoreMinimal.h"

#include "resource_accessors.generated.h"

UCLASS()
/**
 * @brief Vanilla electric accessor BlockLogic
 */
class UElectricAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()
  public:
    UElectricAccessor *GetOutsideAccessorCached();
    const UElectricAccessor *GetOutsideAccessorCached() const;

  protected:
    virtual UBaseInventoryAccessor *GetAutoOutsideAccessor() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla electric conductor BlockLogic
 */
class UElectricConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricConductorAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla electric input BlockLogic
 */
class UElectricInputAccessor : public UElectricAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricInputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla electric output BlockLogic
 */
class UElectricOutputAccessor : public UElectricAccessor {
    GENERATED_BODY()
  public:
    UElectricOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricOutputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid accessor BlockLogic
 */
class UFluidAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()
  public:
    UFluidAccessor *GetOutsideAccessorCached();
    const UFluidAccessor *GetOutsideAccessorCached() const;

  protected:
    virtual UBaseInventoryAccessor *GetAutoOutsideAccessor() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid conductor BlockLogic
 */
class UFluidConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidConductorAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid input BlockLogic
 */
class UFluidInputAccessor : public UFluidAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidInputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid output BlockLogic
 */
class UFluidOutputAccessor : public UFluidAccessor {
    GENERATED_BODY()
  public:
    UFluidOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidOutputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat accessor BlockLogic
 */
class UHeatAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()
  public:
    UHeatAccessor *GetOutsideAccessorCached();
    const UHeatAccessor *GetOutsideAccessorCached() const;

  protected:
    virtual UBaseInventoryAccessor *GetAutoOutsideAccessor() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat conductor BlockLogic
 */
class UHeatConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatConductorAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat input BlockLogic
 */
class UHeatInputAccessor : public UHeatAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatInputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat output BlockLogic
 */
class UHeatOutputAccessor : public UHeatAccessor {
    GENERATED_BODY()
  public:
    UHeatOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatOutputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic accessor BlockLogic
 */
class UKineticAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()

  public:
    UKineticAccessor *GetOutsideAccessorCached();
    const UKineticAccessor *GetOutsideAccessorCached() const;

  protected:
    virtual UBaseInventoryAccessor *GetAutoOutsideAccessor() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic conductor BlockLogic
 */
class UKineticConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticConductorAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic input BlockLogic
 */
class UKineticInputAccessor : public UKineticAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticInputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic output BlockLogic
 */
class UKineticOutputAccessor : public UKineticAccessor {
    GENERATED_BODY()

  public:
    UKineticOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticOutputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data accessor BlockLogic
 */
class UDataAccessor : public UDataInventoryAccessor {
    GENERATED_BODY()
  public:
    UDataAccessor *GetOutsideAccessorCached();
    const UDataAccessor *GetOutsideAccessorCached() const;

  protected:
    virtual UBaseInventoryAccessor *GetAutoOutsideAccessor() override;

  public:
    EVO_LUA_CODEGEN_DB_EX(DataAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data conductor BlockLogic
 */
class UDataConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(DataConductorAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data input BlockLogic
 */
class UDataInputAccessor : public UDataAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(DataInputAccessor);
    static void RegisterLua(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data output BlockLogic
 */
class UDataOutputAccessor : public UDataAccessor {
    GENERATED_BODY()
  public:
    UDataOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(DataOutputAccessor);
    static void RegisterLua(lua_State *L);
};