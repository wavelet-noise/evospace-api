// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "tesselator.h"
#include "Core/prototype.h"

#include "tesselator_cube.generated.h"

class UMaterialInterface;
/**
 * @brief Tesselator cube
 */
UCLASS()
class UTesselatorCube : public UTesselator {
    GENERATED_BODY()

  public:
    virtual int GenerateMesh(
        const struct SectorCompilerData &in, MeshDataArray &data, const Vec3i &pos
    ) const override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    void set_material(UMaterialInterface *material);

    virtual bool TempIsMarching() const override { return false; }

  protected:
    UPROPERTY(EditAnywhere)
    UMaterialInterface *mMaterialNorth = nullptr;

    UPROPERTY(EditAnywhere)
    UMaterialInterface *mMaterialSouth = nullptr;

    UPROPERTY(EditAnywhere)
    UMaterialInterface *mMaterialWest = nullptr;

    UPROPERTY(EditAnywhere)
    UMaterialInterface *mMaterialEast = nullptr;

    UPROPERTY(EditAnywhere)
    UMaterialInterface *mMaterialTop = nullptr;

    UPROPERTY(EditAnywhere)
    UMaterialInterface *mMaterialDown = nullptr;

  private:
    static int32 GetSectionMaterial(MeshDataArray &data, UMaterialInterface *material);

  public:
    EVO_LUA_CODEGEN_DB(UTesselatorCube, TesselatorCube);
    static void RegisterLua(lua_State *L);
};
