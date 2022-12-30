#pragma once

class UBlockLogic;
class UTieredBlockLogic;
class UCrafterBase;
class USelectCrafter;
class UAutoCrafter;
class UItem;
class URecipeDictionary;
class UBlock;
class UTesselator;
class UTesselatorCube;
class UItemLogic;
class UBlockBuilder;
class UBaseAccessor;
class UBaseInventoryAccessor;
class UInventoryReader;
class UInventoryAccess;
class UBaseInventory;
class UInventory;
class UInventoryContainer;
class UInternalInventory;
class URecipeInventory;

namespace evo { namespace prototype_helper {
inline std::tuple<
    UBlockLogic *, UTieredBlockLogic *, UCrafterBase *, USelectCrafter *,
    UAutoCrafter *, UItem *, URecipeDictionary *, UBlock *, UTesselator *,
    UTesselatorCube *, UItemLogic *, UBlockBuilder *, UBaseAccessor *,
    UBaseInventoryAccessor *, UInventoryReader *, UInventoryAccess *, UBaseInventory *,
    UInventory *, UInventoryContainer *, UInternalInventory *,
    URecipeInventory *>
    classes;
}} // namespace evo::prototype_helper