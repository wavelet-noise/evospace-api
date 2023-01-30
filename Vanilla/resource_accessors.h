// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/Blocks/BaseInventorySideAccessor.h"

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
};

UCLASS()
/**
 * @brief Vanilla electric conductor BlockLogic
 */
class UElectricConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()
};
UCLASS()
/**
 * @brief Vanilla electric input BlockLogic
 */
class UElectricInputAccessor : public UElectricAccessor {
    GENERATED_BODY()
};
UCLASS()
/**
 * @brief Vanilla electric output BlockLogic
 */
class UElectricOutputAccessor : public UElectricAccessor {
    GENERATED_BODY()
  public:
    UElectricOutputAccessor();
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
};

UCLASS()
/**
 * @brief Vanilla fluid conductor BlockLogic
 */
class UFluidConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()
};

UCLASS()
/**
 * @brief Vanilla fluid input BlockLogic
 */
class UFluidInputAccessor : public UFluidAccessor {
    GENERATED_BODY()
};
UCLASS()
/**
 * @brief Vanilla fluid output BlockLogic
 */
class UFluidOutputAccessor : public UFluidAccessor {
    GENERATED_BODY()
  public:
    UFluidOutputAccessor();
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
};

UCLASS()
/**
 * @brief Vanilla heat conductor BlockLogic
 */
class UHeatConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()
};
UCLASS()
/**
 * @brief Vanilla heat input BlockLogic
 */
class UHeatInputAccessor : public UHeatAccessor {
    GENERATED_BODY()
};

UCLASS()
/**
 * @brief Vanilla heat output BlockLogic
 */
class UHeatOutputAccessor : public UHeatAccessor {
    GENERATED_BODY()
  public:
    UHeatOutputAccessor();
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
};

UCLASS()
/**
 * @brief Vanilla kinetic conductor BlockLogic
 */
class UKineticConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()
};

UCLASS()
/**
 * @brief Vanilla kinetic input BlockLogic
 */
class UKineticInputAccessor : public UKineticAccessor {
    GENERATED_BODY()
};

UCLASS()
/**
 * @brief Vanilla kinetic output BlockLogic
 */
class UKineticOutputAccessor : public UKineticAccessor {
    GENERATED_BODY()

  public:
    UKineticOutputAccessor();
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
};

UCLASS()
/**
 * @brief Vanilla data conductor BlockLogic
 */
class UDataConductorAccessor : public UBaseAccessor {
    GENERATED_BODY()
};

UCLASS()
/**
 * @brief Vanilla data input BlockLogic
 */
class UDataInputAccessor : public UDataAccessor {
    GENERATED_BODY()
};

UCLASS()
/**
 * @brief Vanilla data output BlockLogic
 */
class UDataOutputAccessor : public UDataAccessor {
    GENERATED_BODY()
  public:
    UDataOutputAccessor();
};