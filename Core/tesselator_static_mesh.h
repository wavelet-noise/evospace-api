// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "tesselator.h"

#include "TesselatorStaticMesh.generated.h"

class UStaticMesh;
class UMaterialInterface;

/**
 *
 */
UCLASS()
class UTesselatorStaticMesh : public UTesselator {
    GENERATED_BODY()

  public:
    virtual int GenerateMesh(
        const struct SectorCompilerData &in, MeshDataArray &data, const Vec3i &pos
    ) const override;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    virtual bool TempIsMarching() const override { return false; }

    UFUNCTION(BlueprintCallable)
    void SetStaticMesh(const UStaticMesh *mesh);

  private:
    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    const UStaticMesh *mMesh;

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UMaterialInterface *mMaterial;

    int32 GetSectionMaterial(MeshDataArray &data, UMaterialInterface *material) const;
};
