#pragma once

class UPrototype;
class UEntity;
class UBlockLogic;
class UTieredBlock;
class UFilteringBlock;
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
class UBrushBreaker;
class UBaseAccessor;
class UBaseInventoryAccessor;
class UInventoryReader;
class UInventoryAccess;
class UBaseInventory;
class UInventory;
class USingleSlotInventory;
class UInventoryContainer;
class UInternalInventory;
class URecipeInventory;

class UBaseItemFilter;
class UItemBlackFilter;
class UItemWhiteFilter;
class UItemInventoryFilter;

class UPropsGenerator;
class ULayeringGenerator;
class UBiome;
class UStaticAttach;
class UPropList;
class UStaticResearch;
class UStaticChapter;

class UBedLogic;
class UDoorLogic;
class ULampLogic;
class UFenceLogic;

class USurfaceBuilder;
class UPlaneBuilder;

class UFissionReactor;
class UFusionReactor;

class URobotArm;
class UFilteringRobotArm;

class UPump;
class UDiode;
class UFilteringPump;

class UStorageBlock;
class UChest;
class UItemRack;

class UConductor;
class UHeatConductor;
class UKineticConductor;
class UFluidConductor;
class UDataConductor;
class UElectricConductor;

class UFluidContainer;

class USwitch;
class UKineticSwitch;
class UHeatSwitch;
class UFluidSwitch;
class UDataSwitch;
class UElectricSwitch;

class UBatteryBox;

class UConveyor;
class USplitter;
class USorter;

class UPortal;

class USignBlock;
class UMonitor;

class UComputer;
class UQuantumComputer;

class UMinerBase;
class UDrillingRig;
class UPumpjack;

class ULuaBlock;

class UDeconstructorCrafter;
class UDumpCrafter;
class UDumpAnyCrafter;

class ULogicCircuit;
class ULogicDisplay;
class ULogicController;
class ULogicInterface;

class UCoreAccessor;

class UHandGenerator;

#define ACCESSOR_FORWARD_CODEGEN(NAME)                                         \
    class U##NAME##Accessor;                                                   \
    class U##NAME##InputAccessor;                                              \
    class U##NAME##OutputAccessor;                                             \
    class U##NAME##ConductorAccessor;

#define ACCESSOR_CLASS_CODEGEN(NAME)                                           \
    U##NAME##Accessor *, U##NAME##InputAccessor *, U##NAME##OutputAccessor *,  \
        U##NAME##ConductorAccessor *

ACCESSOR_FORWARD_CODEGEN(Fluid)
ACCESSOR_FORWARD_CODEGEN(Electric)
ACCESSOR_FORWARD_CODEGEN(Heat)
ACCESSOR_FORWARD_CODEGEN(Kinetic)
ACCESSOR_FORWARD_CODEGEN(Data)

namespace evo { namespace prototype_helper {
inline std::tuple<
    UPrototype *, UEntity *, UBlockLogic *, UTieredBlock *, UFilteringBlock *,
    UCrafterBase *, USelectCrafter *, UAutoCrafter *, UItem *,
    URecipeDictionary *, UBlock *, UTesselator *, UTesselatorCube *,
    UTesselatorMarching *, UItemLogic *, UBlockBuilder *, UBrushBreaker *,
    UBaseAccessor *, UBaseInventoryAccessor *, UInventoryReader *,
    UInventoryAccess *, UBaseInventory *, UInventory *, USingleSlotInventory *,
    UInventoryContainer *, UInternalInventory *, URecipeInventory *,
    UPropsGenerator *, ULayeringGenerator *, UBiome *, UStaticAttach *,
    UPropList *, UStaticResearch *, UStaticChapter *, UBedLogic *, UDoorLogic *,
    ULampLogic *, UFenceLogic *, USurfaceBuilder *, UPlaneBuilder *,
    UFissionReactor *, UFusionReactor *, URobotArm *, UFilteringRobotArm *,
    UPump *, UDiode *, UFilteringPump *, UStorageBlock *, UChest *, UItemRack *,
    UConductor *, UHeatConductor *, UKineticConductor *, UFluidConductor *,
    UDataConductor *, UElectricConductor *, UFluidContainer *, USwitch *,
    UKineticSwitch *, UHeatSwitch *, UFluidSwitch *, UDataSwitch *,
    UElectricSwitch *, UBatteryBox *, UConveyor *, USplitter *, USorter *,
    UPortal *, USignBlock *, UMonitor *, UComputer *, UQuantumComputer *,
    ULuaBlock *, UMinerBase *, UDrillingRig *, UPumpjack *,
    UDeconstructorCrafter *, UDumpCrafter *, UDumpAnyCrafter *, ULogicCircuit *,
    ULogicDisplay *, ULogicController *, ULogicInterface *, UCoreAccessor *,
    UHandGenerator *, ACCESSOR_CLASS_CODEGEN(Fluid),
    ACCESSOR_CLASS_CODEGEN(Electric), ACCESSOR_CLASS_CODEGEN(Heat),
    ACCESSOR_CLASS_CODEGEN(Kinetic), ACCESSOR_CLASS_CODEGEN(Data)>
    classes;

#undef ACCESSOR_FORWARD_CODEGEN
#undef ACCESSOR_CLASS_CODEGEN

}} // namespace evo::prototype_helper