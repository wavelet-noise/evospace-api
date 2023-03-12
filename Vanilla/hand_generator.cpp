#include "hand_generator.h"

#include "Core/single_slot_inventory.h"
#include "Evospace/Dimension.h"
#include "resource_accessors.h"
#include "Evospace/JsonHelper.h"

UHandGenerator::UHandGenerator() {
    inventory = CreateDefaultSubobject<USingleSlotInventory>("inventory");
    accessor = CreateDefaultAccessor<UKineticOutputAccessor>("kinetic_output");
    accessor->Bind(inventory);
    accessor->SetSidePos(Side::Back, Vec3i::Zero());
    inventory->capacity = power * 3;
}

bool UHandGenerator::is_block_tick() const { return true; }

void UHandGenerator::OnGeneratorPressed() {
    if (stored + per_click < max_stored) {
        AwakeAnimation();
        stored += per_click;
    } else {
        stored = max_stored;
    }
}

void UHandGenerator::OnAction(
    const FHitResult &hit, const Vec3i &side, AItemLogicActor *item
) {
    Super::OnAction(hit, side, item);
    OnGeneratorPressed();
}
bool UHandGenerator::DeserializeJson(TSharedPtr<FJsonObject> json) {
    auto result = Super::DeserializeJson(json);
    json_helper::TryGet(json, "stored", stored);
    return result;
}
bool UHandGenerator::SerializeJson(TSharedPtr<FJsonObject> json) {
    auto result = Super::SerializeJson(json);
    json_helper::TrySet(json, "stored", stored);
    return result;
}

void UHandGenerator::Tick() {
    // UTieredBlock::Tick(); // is empty
    if (stored >= power && inventory->get(0).count < power) {
        AwakeAnimation();
        inventory->add(FItemData(evo::DB::find<UItem>("Kinetic"), power));
        stored -= power;
    }

    if (stored < power) {
        stored = 0;
    }
}

void UHandGenerator::lua_reg(lua_State *L) {
    luabridge::getGlobalNamespace(L)
        .deriveClass<UHandGenerator, UTieredBlock>("HandGenerator")
        .addProperty("per_click", &UHandGenerator::per_click)
        .addProperty("power", &UHandGenerator::power)
        .addProperty("stored", &UHandGenerator::stored)
        .addProperty("max_stored", &UHandGenerator::max_stored)
        .endClass();
}