// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Prototype.h"
#include "Evospace/BreakResult.h"
#include "Evospace/CoordinameMinimal.h"
#include "Evospace/SerializableJson.h"
#include "Evospace/Vector.h"

#include "BlockLogic.generated.h"

class ABlockActor;
class UBlockWidget;
DECLARE_STATS_GROUP(TEXT("BLOCKLOGIC_Game"), STATGROUP_BLOCKLOGIC,
                    STATCAT_Advanced);

class UHudWidget;
class URootBlockComponent;

class ADimension;
class AItemLogic;
class UStaticItem;
class UInventoryAccess;
class UStaticBlock;
class UBaseAccessor;

UCLASS(BlueprintType)
/**
 * 
 */
class EVOSPACE_API UBlockLogic : public UObject, public ISerializableJson {
  GENERATED_BODY()

  protected:
  // events

  UBlockLogic();

  public:
  //    ?
  //   BlockBeginPlay
  virtual void NeighborBlockAdded(UBlockLogic *block, const Vec3i &pos);
  virtual void NeighborBlockRemoved(UBlockLogic *block, const Vec3i &pos);

  virtual void SideAccessorAdded(UBaseAccessor *accessor, const Vec3i &side,
                                 const Vec3i &pos);
  virtual void SideAccessorRemoved(UBaseAccessor *accessor, const Vec3i &side,
                                   const Vec3i &pos);

  virtual void SpawnedByItem(AItemLogic *item);
  virtual EBreakResult RemovedByItem(AItemLogic *item);

  virtual Vec3i GetRotationLocks() const;

  virtual bool IsHandleRecipeSelection() const;
  virtual void HandleRecipeSelection(UStaticItem *item);

  virtual void SetActor(ABlockActor *actor);
  void DeferredPaintApply() const;
  virtual void RemoveActor();

  virtual void LuaBlock();
  virtual void BlockDestruction();

  virtual bool IsBlockTicks() const;
  virtual void Tick();
  virtual void TickAccessor();

  virtual void ReplaceWith(UBlockLogic *other);

  /**
   * @brief Test if position is suitable for this block placing
   *
   * Some places are not suitable for block placing but still not occupied.
   * For example when such block will connect two pipe systems with different
   * content
   * @param dim dimension instance for test
   * @param pos position for test
   * @return
   */
  virtual bool CheckPlaceble(ADimension *dim, FVector3i pos);

  UFUNCTION(BlueprintCallable)
  /**
   * @brief Try to awake actor in world for animation playing
   */
  virtual void AwakeAnimation() const;

  UFUNCTION(BlueprintCallable)
  /**
   * @brief Try to make sleep actor in world for stopping animation playing
   */
  virtual void SleepAnimation() const;

  // No any code
  virtual bool SaveSettings(TSharedPtr<FJsonObject> json,
                            AMainPlayerController *mpc = nullptr);

  // No any code
  virtual bool LoadSettings(TSharedPtr<FJsonObject> json,
                            AMainPlayerController *mpc = nullptr);

  UFUNCTION(BlueprintCallable)
  virtual FString SaveSettings(AMainPlayerController *mpc = nullptr);

  UFUNCTION(BlueprintCallable)
  virtual void LoadSettings(const FString &json,
                            AMainPlayerController *mpc = nullptr);

  UFUNCTION(BlueprintCallable)
  void PaintBlock(UMaterialInterface *mat);

  Vec3i GetBlockPos() const;
  void SetBlockPos(const Vec3i &pos);

  virtual UBlockLogic *GetPartRootBlock();

  virtual UBlockLogic *GetWidgetRootBlock();

  FQuat GetBlockQuat() const;
  void SetBlockQuat(const FQuat &r);

  void SetActorMobility(EComponentMobility::Type movable);

  float DeltaTime = 0.05f;

  UFUNCTION(BlueprintCallable)
  virtual TSubclassOf<UBlockWidget> GetWidgetClass() const;

  UFUNCTION(BlueprintCallable)
  virtual EBlockWidgetType GetWidgetType() const;

  virtual void InitializeBlock();

  // No any code
  virtual void BlockBeginPlay();

  // No any code
  virtual void BlockEndPlay();

  FTransform GetTransform() const;

  FVector GetLocation() const;

  void SetOwner(void *param1);

  UBaseAccessor *GetSideAccessor(UClass *type, Vec3i side, Vec3i pos);

  template <class Ty_>
  Ty_ *GetSideAccessor(FVector3i side, FVector3i pos) {
    return Cast<Ty_>(GetSideAccessor(Ty_::StaticClass(), side, pos));
  }

  UBaseAccessor *GetCoreAccessor(UClass *type);

  template <class Ty_>
  Ty_ *GetCoreAccessor() {
    return Cast<Ty_>(GetCoreAccessor(Ty_::StaticClass()));
  }

  template <typename Ty_>
  Ty_ *CreateDefaultAccessor(UObject *Outer, FName SubobjectFName) {
    auto v = CreateDefaultSubobject<Ty_>(Outer, SubobjectFName);
    RegisterComponent(v);
    return v;
  }

  template <typename Ty_>
  Ty_ *CreateAccessor(FName Name) {
    auto v = NewObject<Ty_>(this, Name);
    RegisterComponent(v);
    return v;
  }

  template <typename Ty_>
  Ty_ *CreateDefaultAccessor(FName SubobjectFName) {
    auto v = CreateDefaultSubobject<Ty_>(SubobjectFName);
    RegisterComponent(v);
    return v;
  }

  public:
  ADimension *GetDimension() const;
  void SetDimension(ADimension *dim);

  //=====================

  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
  virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

  void SetStaticBlock(const UStaticBlock *static_block);

  virtual const UStaticBlock *GetStaticBlock() const;

  // ************************************* //

  virtual void OpenWidget(class UHudWidget *widget);

  virtual void OnAction(const FHitResult &hit, const Vec3i &side,
                        AItemLogic *item);

  UFUNCTION(BlueprintCallable, BlueprintPure)
  virtual bool ActionAndWidget() const;

  //    .
  virtual int32 DropItems(UInventoryAccess *inventory);

  void SpawnDropItems(APlayerController *pc);

  void RegisterComponent(UBaseAccessor *c);

  virtual TArray<UBaseAccessor *> GetAccessors();

  virtual ABlockActor *GetActor();

  UPROPERTY(BlueprintReadOnly, VisibleAnywhere,
            meta = (AllowPrivateAccess = "true"))
  const UStaticBlock *mStaticBlock = nullptr;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  ABlockActor *mActor = nullptr;

  UPROPERTY(VisibleAnywhere)
  FVector3i mPos = {};

  UPROPERTY(VisibleAnywhere)
  FQuat mQuat = FQuat(EForceInit::ForceInitToZero);

  UPROPERTY(VisibleAnywhere)
  TArray<UBaseAccessor *> mAccessors;

  UPROPERTY()
  ADimension *mDimension;

  //mutable int32 mFromLastWakeup = 0;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UMaterialInterface *mPaintMaterial;

  public:
  EVO_LUA_CODEGEN_DB_EX(BlockLogic);
  static void lua_reg(lua_State *L);
};

UCLASS(BlueprintType)
class EVOSPACE_API UPartBlockLogic : public UBlockLogic {
  GENERATED_BODY()

  public:
  virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
  virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

  UBlockLogic *mParentBlock;

  virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

  virtual void OpenWidget(class UHudWidget *widget) override;

  virtual UBlockLogic *GetPartRootBlock() override;

  virtual TArray<UBaseAccessor *> GetAccessors() override;

  virtual ABlockActor *GetActor() override;

  virtual void SetActor(ABlockActor *actor);

  virtual void OnAction(const FHitResult &hit, const Vec3i &side,
                        AItemLogic *item);
};