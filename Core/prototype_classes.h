#pragma once

class UBlockBuilder;
class UItemLogic;
class UTesselatorCube;
class UTesselator;
class UBlock;
class URecipeDictionary;
class UItem;
class UAutoCrafter;
class USelectCrafter;
class UCrafterBase;
class UTieredBlockLogic;
class UBlockLogic;
class UBaseAccessor;
class UBaseInventoryAccessor;

namespace evo { namespace prototype_helper {
inline std::tuple<
    UBlockLogic *, UTieredBlockLogic *, UCrafterBase *, USelectCrafter *,
    UAutoCrafter *, UItem *, URecipeDictionary *, UBlock *, UTesselator *,
    UTesselatorCube *, UItemLogic *, UBlockBuilder *, UBaseAccessor *,
    UBaseInventoryAccessor *>
    classes;
}} // namespace evo::prototype_helper