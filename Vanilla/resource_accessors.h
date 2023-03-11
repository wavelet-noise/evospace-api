// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/base_inventory_accessor.h"
#include "Core/prototype.h"
#include "CoreMinimal.h"

#include "resource_accessors.generated.h"

UCLASS()
/**
 * @brief Vanilla electric accessor
 */
class UElectricAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla electric conductor accessor
 */
class UElectricConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricConductorAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla electric input accessor
 */
class UElectricInputAccessor : public UElectricAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricInputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla electric output accessor
 */
class UElectricOutputAccessor : public UElectricAccessor {
    GENERATED_BODY()
  public:
    UElectricOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(ElectricOutputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid accessor
 */
class UFluidAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid conductor accessor
 */
class UFluidConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidConductorAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid input accessor
 */
class UFluidInputAccessor : public UFluidAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidInputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla fluid output accessor
 */
class UFluidOutputAccessor : public UFluidAccessor {
    GENERATED_BODY()
  public:
    UFluidOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(FluidOutputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat accessor
 */
class UHeatAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat conductor accessor
 */
class UHeatConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatConductorAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat input accessor
 */
class UHeatInputAccessor : public UHeatAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatInputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla heat output accessor
 */
class UHeatOutputAccessor : public UHeatAccessor {
    GENERATED_BODY()
  public:
    UHeatOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(HeatOutputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic accessor
 */
class UKineticAccessor : public UBaseInventoryAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic conductor accessor
 */
class UKineticConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticConductorAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic input accessor
 */
class UKineticInputAccessor : public UKineticAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticInputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla kinetic output accessor
 */
class UKineticOutputAccessor : public UKineticAccessor {
    GENERATED_BODY()

  public:
    UKineticOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(KineticOutputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data accessor
 */
class UDataAccessor : public UDataInventoryAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(DataAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data conductor accessor
 */
class UDataConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(DataConductorAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data input accessor
 */
class UDataInputAccessor : public UDataAccessor {
    GENERATED_BODY()

  public:
    EVO_LUA_CODEGEN_DB_EX(DataInputAccessor);
    static void lua_reg(lua_State *L);
};

UCLASS()
/**
 * @brief Vanilla data output accessor
 */
class UDataOutputAccessor : public UDataAccessor {
    GENERATED_BODY()
  public:
    UDataOutputAccessor() { auto_output = true; }

  public:
    EVO_LUA_CODEGEN_DB_EX(DataOutputAccessor);
    static void lua_reg(lua_State *L);
};