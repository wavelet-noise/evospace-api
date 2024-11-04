#pragma once
#include "Public/WorldGenerator.h"
#include "LuaWorldGenerator.generated.h"

class UHeightGenerator;
class UBiomeFamily;

UCLASS()
/**
 * LuaWorldGenerator
 */
class ULuaWorldGenerator : public UWorldGenerator {
  GENERATED_BODY()
  public:
  UPROPERTY()
  UBiomeFamily *mBiomeFamily = nullptr;

  UPROPERTY()
  UHeightGenerator *mHeight;

  virtual void Generate(FColumnSectorsData &data, const Vec3i &pos) const override;
  virtual void GenerateGlobal(FColumnMaps &data, const FVector &pos, float Scale = 1.f, int32 height_width = 16, bool no_biom = false) const override;

  public:
  EVO_OWNED(LuaWorldGenerator, WorldGenerator)
  EVO_CODEGEN(LuaWorldGenerator, WorldGenerator)
  virtual void lua_reg(lua_State *L) const override {
    luabridge::getGlobalNamespace(L)
      .deriveClass<ULuaWorldGenerator, UWorldGenerator>("LuaWorldGenerator")
      .addProperty("biome_family", &ULuaWorldGenerator::mBiomeFamily)
      .addProperty("height", &ULuaWorldGenerator::mHeight)
      .endClass();
  }
};