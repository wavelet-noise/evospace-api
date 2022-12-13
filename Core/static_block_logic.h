#pragma once
#include "Evospace/Shared/bases.h"
#include "static_block_logic.generated.h"

class AItemLogic;
/**
 * @brief Base part of logic entity
 */

UCLASS()
class UStaticBlockLogic : public UObject,
                          public evo::BaseHelper<UStaticBlockLogic> {
    GENERATED_BODY()

    // Lua api
  public:
    //
  public:
    
    static std::function<void(lua_State *)> GetRegisterLambda() { return {}; }

    virtual void NeighborBlockAdded(UStaticBlockLogic *block, const Vec3i &pos) {}
    virtual void NeighborBlockRemoved(UStaticBlockLogic *block, const Vec3i &pos) {}

    virtual void SideAccessorAdded(
        UBaseAccessor *accessor, const Vec3i &side, const Vec3i &pos
    ) {}
    virtual void SideAccessorRemoved(
        UBaseAccessor *accessor, const Vec3i &side, const Vec3i &pos
    ) {}

    virtual void SpawnedByItem(AItemLogic *item) {}
    virtual EBreakResult RemovedByItem(AItemLogic *item) { return EBreakResult::Breaked; }

    virtual Vec3i GetRotationLocks() const { return {0, 0, 0}; }

    virtual bool IsHandleRecipeSelection() const { return false; }
    virtual void HandleRecipeSelection(UStaticItem *item) {}

    //std::vector<std::tuple<std::string, evo::EntityFactory::FactoryType::ComponentFuncTuple, void *>> mFuncTuples;
};
EVO_REGISTER_STATIC(UStaticBlockLogic, StaticBlockLogic);
