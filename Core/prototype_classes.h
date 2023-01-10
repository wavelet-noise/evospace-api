#pragma once

class UEntity;
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
class UTesselatorMarching;
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

class UPropsGenerator;
class ULayeringGenerator;
class UBiome;
class UStaticAttach;
class UPropList;
class UStaticResearch;
class UStaticChapter;

class UBedBlockLogic;
class UDoorBlockLogic;
class ULampBlockLogic;
class UFenceBlockLogic;

class USurfaceBuilder;
class UPlaneBuilder;
 
namespace evo { namespace prototype_helper {
inline std::tuple<
    UEntity *, UBlockLogic *, UTieredBlockLogic *, UCrafterBase *, USelectCrafter *,
    UAutoCrafter *, UItem *, URecipeDictionary *, UBlock *, UTesselator *,
    UTesselatorCube *, UTesselatorMarching *, UItemLogic *, UBlockBuilder *, UBaseAccessor *,
    UBaseInventoryAccessor *, UInventoryReader *, UInventoryAccess *, UBaseInventory *,
    UInventory *, UInventoryContainer *, UInternalInventory *,
    URecipeInventory *, UPropsGenerator *, ULayeringGenerator *, UBiome*, UStaticAttach *,
    UPropList *, UStaticResearch *, UStaticChapter * , UBedBlockLogic *, UDoorBlockLogic *,
    ULampBlockLogic *, UFenceBlockLogic *, USurfaceBuilder * , UPlaneBuilder *
>
    classes;
}} // namespace evo::prototype_helper