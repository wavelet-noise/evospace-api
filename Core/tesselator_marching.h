// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "tesselator.h"

#include <Math/Vector.h>

#include "tesselator_marching.generated.h"

class UMaterialInterface;
struct SectorCompilerData;

struct GRIDCELL {
    FVector p[8];
    double val[8];
    float wetness[8];
    float r_side[8];
    float g_side[8];
    float b_side[8];
    float r_top[8];
    float g_top[8];
    float b_top[8];
    float color_mask[8];
};

UCLASS()
/**
 * @brief Tesselator marching surface
 */
class UTesselatorMarching : public UTesselator {
    GENERATED_BODY()

  public:
    void set_material(UMaterialInterface *material) { mMaterial = material; }

  public:
    virtual int GenerateMesh(
        const struct SectorCompilerData &in, MeshDataArray &data,
        const Vec3i &pos
    ) const override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool TempIsMarching() const override { return true; }

  protected:
    virtual void PostLoad() override;

  protected:
    UPROPERTY()
    UMaterialInterface *mMaterial = nullptr;

    float mIsoLevel = (255.0f * 7.0f) / 8.0f; // 32.0f;

  private:
    void Polygonise(
        const struct SectorCompilerData &in, const GRIDCELL &grid,
        double isolevel, MeshDataArray &data, const Vec3f &pos,
        const Vec3f &size
    ) const;

    void PolygoniseCube(
        const struct SectorCompilerData &in, MeshDataArray &data,
        const Vec3i &bpos
    ) const;

    FVector VertexInterp(
        double isolevel, const FVector &p1, const FVector &p2, double valp1,
        double valp2
    ) const;

    float TrilinearInterp(
        const FVector *pos, const float *val, const FVector &point
    ) const;

  private:
    int32
    GetSectionMaterial(MeshDataArray &data, UMaterialInterface *material) const;

  public:
    EVO_LUA_CODEGEN_DB(UTesselatorMarching, TesselatorMarching);
    static void RegisterLua(lua_State *L);
};
