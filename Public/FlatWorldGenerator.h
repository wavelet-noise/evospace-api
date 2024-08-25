// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.

#pragma once

#include "../BlockCell.h"
#include "../CoordinateSystem.h"
#include "../WorldGenerator.h"
#include "CoreMinimal.h"

#include "FlatWorldGenerator.generated.h"

class UStaticBlock;

UCLASS(BlueprintType)
/**
 *  Legacy flat concrete world generator
 */
class UFlatWorldGenerator : public UWorldGenerator {
  GENERATED_BODY()

  public:
  UFlatWorldGenerator();

  virtual void Generate(FColumnSectorsData &data, const Vec3i &sector_pos) const override;
  virtual void GenerateGlobal(FColumnMaps &data, const FVector &pos, float Scale = 1.f, int32 height_width = 16, bool no_biom = false) const;
  virtual int32 GetHeight(const FVector2i &where) const;

  protected:
  virtual void Initialize() override;

  private:
  TArray<UStaticBlock *> mBlocks;
};
