#pragma once
#include "Prototype.h"
#include "Evospace/SerializableJson.h"
#include "Evospace/Vector.h"
#include <Evospace/Common.h>
#include "StaticResearch.generated.h"

class AMainPlayerController;
class UInventory;

UCLASS(BlueprintType)
class EVOSPACE_API UOldResearch : public UObject, public ISerializableJson {
  GENERATED_BODY()

  public:
  virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;
  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  TArray<UStaticItem *> mItems;
  TArray<int64> mValues;
};

UENUM()
enum class EResearchStatus : uint8 {
  Opened,
  PartComplete,
  Closed,
  Complete,
  Restricted
};

USTRUCT(BlueprintType)
struct EVOSPACE_API FResearchUnlock {
  GENERATED_BODY()

  public:
  FName Dictionary;
  FName Recipe;
};

USTRUCT(BlueprintType)
struct EVOSPACE_API FResearchUnlockLevel {
  GENERATED_BODY()

  public:
  TArray<FResearchUnlock> Unlocks;

  UPROPERTY()
  TArray<class URecipe *> Recipes;
};

UCLASS(BlueprintType)
class EVOSPACE_API UStaticResearch : public UPrototype {
  GENERATED_BODY()

  public:
  UStaticResearch();

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  TArray<FKeyTableObject> LabelParts = {};

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UTexture2D *Texture = nullptr;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  TArray<UStaticResearch *> RequiredResearches = {};

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  TArray<FName> RequiredResearchesNames = {};

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  TArray<UInventory *> DataPoints;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventory *NewItemsCache;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  TArray<FResearchUnlockLevel> Unlocks;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UInventory *AlsoNewItemsCache;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  FResearchUnlockLevel AlsoUnlocks;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  bool mCompleteByDefault = false;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int Level = 0;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FVector2i LevelMinMax;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  EResearchStatus Type;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  bool MainResearch = false;

  UFUNCTION(BlueprintCallable, BlueprintCosmetic)
  FText GetLabel() const;

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  virtual void PostDeserializeJson() override;

  virtual void ApplyToController(AMainPlayerController *apply_to, int32 level);

  EVO_LUA_CODEGEN_DB_EX(StaticResearch, StaticResearch)
  virtual void lua_reg(lua_State *L) const override {}
};

UCLASS(BlueprintType)
class EVOSPACE_API UStaticResearchBonusInventory : public UStaticResearch {
  GENERATED_BODY()
  public:
  virtual void ApplyToController(AMainPlayerController *apply_to, int32 level) override;

  EVO_LUA_CODEGEN_DB_EX(StaticResearchBonusInventory, StaticResearch)
  virtual void lua_reg(lua_State *L) const override {}
};

UCLASS(BlueprintType)
class EVOSPACE_API UStaticResearchModifier : public UStaticResearch {
  GENERATED_BODY()
  public:
  virtual void ApplyToController(AMainPlayerController *apply_to, int32 level) override;

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  class UStaticModifier *mModifier = nullptr;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  float mBonusValue;

  EVO_LUA_CODEGEN_DB_EX(StaticResearchModifier, StaticResearch)
  virtual void lua_reg(lua_State *L) const override {}
};

UCLASS(BlueprintType)
class EVOSPACE_API UStaticResearchToolUnlock : public UStaticResearch {
  GENERATED_BODY()
  public:
  virtual void ApplyToController(AMainPlayerController *apply_to, int32 level) override;

  EVO_LUA_CODEGEN_DB_EX(StaticResearchToolUnlock, StaticResearch)
  virtual void lua_reg(lua_State *L) const override {}
};