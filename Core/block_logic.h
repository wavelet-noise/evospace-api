// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Core/base_inventory_accessor.h"
#include "Core/prototype.h"
#include "CoreMinimal.h"
#include "Evospace/BlockWidgetType.h"
#include "Evospace/BreakResult.h"
#include "Evospace/CoordinateMinimal.h"
#include "Evospace/SerializableJson.h"

#include "block_logic.generated.h"

DECLARE_STATS_GROUP(
    TEXT("BLOCKLOGIC_Game"), STATGROUP_BLOCKLOGIC, STATCAT_Advanced
);

class UHudWidget;
class URootBlockComponent;

class ADimension;
class AItemLogicActor;
class UItem;
class UInventoryAccess;
class UBlock;
class UBaseAccessor;

UCLASS(BlueprintType)
/**
 * @brief Vanilla most basic BlockLogic
 */
class UBlockLogic : public UPrototype, public ISerializableJson {
    GENERATED_BODY()

    // Lua api
  public:
    /**
     * @brief
     * @return
     */
    virtual bool is_block_tick() const;

    UPROPERTY(BlueprintReadOnly)
    /**
     * @brief Readonly property.
     */
    const UBlock *block = nullptr;

    // Legacy from 0.18.3
    UBaseInventoryAccessor *lua_create_accessor(UClass *type);

    /**
     * @brief
     * @param accessor
     */
    void add_accessor(UBaseAccessor *accessor);

    /**
     * @brief
     * @param com
     */
    void add_component(UPrototype *com, std::string_view name);

    /**
     * @brief
     * @param com
     */
    UPrototype *get_component(std::string_view name) const;

    // Engine code
  public:
    UBlockLogic();

    // Events
  public:
    virtual void OnNeighborBlockAdded(UBlockLogic *neighbour, const Vec3i &pos);
    virtual void
    OnNeighborBlockRemoved(UBlockLogic *neighbour, const Vec3i &pos);
    virtual void OnSideAccessorAdded(
        UBaseAccessor *accessor, const Vec3i &side, const Vec3i &pos
    );
    virtual void OnSideAccessorRemoved(
        UBaseAccessor *accessor, const Vec3i &side, const Vec3i &pos
    );
    virtual void OnSpawnedByItem(AItemLogicActor *item);
    virtual EBreakResult OnRemovedByItem(AItemLogicActor *item);

    //
  public:
    virtual Vec3i GetRotationLocks() const;

    virtual bool IsHandleRecipeSelection() const;
    virtual void HandleRecipeSelection(UItem *item);

    virtual void SetActor(AActor *actor);
    void DeferredPaintApply();
    virtual void RemoveActor();

    virtual void Tick();
    virtual void TickAccessor();

    virtual void EvospacePostDuplicate(const UBlockLogic *proto) {}

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
    virtual bool CheckPlaceble(ADimension *dim, FVector3i pos) const;

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
    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    );

    // No any code
    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    );

    UFUNCTION(BlueprintCallable)
    virtual FString SaveSettings(AMainPlayerController *mpc = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual void
    LoadSettings(const FString &json, AMainPlayerController *mpc = nullptr);

    UFUNCTION(BlueprintCallable)
    void PaintBlock(UMaterialInterface *mat);

    // Absolute
    Vec3i GetBlockPos() const;

    // Absolute
    void SetBlockPos(const Vec3i &pos);

    virtual UBlockLogic *GetRootBlock();

    FQuat GetBlockQuat() const;
    void SetBlockQuat(const FQuat &r);

    UFUNCTION(BlueprintCallable)
    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const;

    UFUNCTION(BlueprintCallable)
    virtual EBlockWidgetType GetWidgetType() const;

    // No any code
    virtual void BlockBeginPlay();

    // No any code
    virtual void BlockEndPlay();

    FTransform GetActorTransform() const;
    FTransform GetTransform() const;

    void SetActorRotation(FQuat param1);

    UBaseAccessor *GetSideAccessor(UClass *type, Vec3i side, Vec3i pos);

    template <class Ty_> Ty_ *GetSideAccessor(Vec3i side, Vec3i pos) {
        return Cast<Ty_>(GetSideAccessor(Ty_::StaticClass(), side, pos));
    }

    UBaseAccessor *GetCoreAccessor(UClass *type);

    template <class Ty_> Ty_ *GetCoreAccessor() {
        return Cast<Ty_>(GetCoreAccessor(Ty_::StaticClass()));
    }

    template <typename Ty_> Ty_ *CreateDefaultAccessor(FName SubobjectFName) {
        auto v = CreateDefaultSubobject<Ty_>(SubobjectFName);
        add_accessor(v);
        return v;
    }

  public:
    ADimension *GetDimension();
    void SetDimention(ADimension *dim);

    //=====================

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    void SetStaticBlock(const UBlock *static_block);

    virtual const UBlock *GetStaticBlock() const;

    // ************************************* //

    virtual void OpenWidget(class UHudWidget *widget);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnAction"))
    void ReceiveOnAction();

    virtual void
    OnAction(const FHitResult &hit, const Vec3i &side, AItemLogicActor *item);

    virtual int32 DropItems(UInventoryAccess *inventory);

    virtual TArray<UBaseAccessor *> &GetAccessors();

    virtual AActor *GetActor();

    UPROPERTY()
    AActor *mActor = nullptr;

    FVector3i mPos = {};

    FQuat mQuat = FQuat(EForceInit::ForceInitToZero);

    UPROPERTY()
    TArray<UBaseAccessor *> accessors;

    UPROPERTY()
    TArray<UPrototype *> components;

    UPROPERTY()
    UMaterialInterface *mPaintMaterial;

  protected:
    UPROPERTY()
    ADimension *dim;

  public:
    EVO_LUA_CODEGEN_DB(UBlockLogic, BlockLogic);
    static void lua_reg(lua_State *L);
};

UCLASS(BlueprintType)
class UPartBlockLogic : public UBlockLogic {
    GENERATED_BODY()

  public:
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;

    UBlockLogic *mParentBlock;

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual void OpenWidget(class UHudWidget *widget) override;

    virtual UBlockLogic *GetRootBlock() override;

    virtual TArray<UBaseAccessor *> &GetAccessors() override;

    virtual AActor *GetActor() override;

    virtual void SetActor(AActor *actor);

    virtual void
    OnAction(const FHitResult &hit, const Vec3i &side, AItemLogicActor *item);
};
