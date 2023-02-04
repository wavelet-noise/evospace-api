// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/CoordinateMinimal.h"
#include "CoreMinimal.h"
#include "Evospace/SerializableJson.h"
#include "Core/prototype.h"

#include <Math/Color.h>
#include <Math/Vector.h>
#include <Math/Vector2D.h>

#include <string>

#include "Tesselator.generated.h"

class UMaterialInterface;
struct SectorCompilerData;

UCLASS(BlueprintType)
/**
 * @brief Tesselator base class
 */
class UTesselator : public UPrototype, public ISerializableJson {
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be
    // inherited to implement this interface.
  public:
    struct MeshData {
        TArray<FVector> Vertices;
        TArray<int32> Triangles;
        TArray<FVector> Normals;
        TArray<FVector2D> UV0;
        TArray<FColor> VertexColors;
        TArray<FVector> Tangents;
        UMaterialInterface *material = nullptr;
    };

    using MeshDataArray = TArray<MeshData>;

    virtual bool TempIsMarching() const { return false; }

    virtual int GenerateMesh(
        const struct SectorCompilerData &in, MeshDataArray &arr,
        const Vec3i &pos
    ) const {
        return 0;
    }

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override {
        return false;
    }

  public:
    EVO_LUA_CODEGEN_DB(UTesselator, Tesselator);
    static void RegisterLua(lua_State *L);
};
