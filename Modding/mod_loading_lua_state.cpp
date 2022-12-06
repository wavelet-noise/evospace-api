#include "mod_loading_lua_state.h"

#include "Evospace/Blocks/AutoCrafterBlockLogic.h"
#include "Evospace/Blocks/BaseInventorySideAccessor.h"
#include "Evospace/Blocks/BlockLogic.h"
#include "Evospace/Item/BaseInventory.h"
#include "Evospace/Item/InventoryContainer.h"
#include "Evospace/JsonObjectLibrary.h"
#include "Evospace/Shared/Core/recipe.h"
#include "Evospace/Shared/Core/recipe_dictionary.h"
#include "Evospace/Shared/static_logger.h"

using namespace luabridge;

namespace evo {
ModLoadingLuaState::ModLoadingLuaState() {

    getGlobalNamespace(L).addFunction(
        "register", &ModLoadingLuaState::RegisterObject
    );

    getGlobalNamespace(L).beginClass<UObject>("Object").endClass();

    getGlobalNamespace(L).beginClass<UClass>("Class").endClass();

    getGlobalNamespace(L)
        .beginClass<UAutoCrafterBlockLogic>("BlockLogic")
        .addFunction(
            "create_accessor", &ModLoadingLuaState::BlockLogicCreateAccessor
        )
        .addFunction(
            "get_input_container", &ModLoadingLuaState::CrafterGetInputContainer
        )
        .addFunction(
            "get_output_container",
            &ModLoadingLuaState::CrafterGetOutputContainer
        )
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UBaseInventoryAccessor>("Accessor")
        .addFunction("set_side_pos", &ModLoadingLuaState::AccessorSetSidePos)
        .addFunction("bind", &ModLoadingLuaState::AccessorBind)
        .endClass();

    getGlobalNamespace(L).addFunction(
        "get_class", &ModLoadingLuaState::GetClass
    );

    getGlobalNamespace(L)
        .beginClass<UInventoryContainer>("InventoryContainer")
        .endClass();

    getGlobalNamespace(L).beginClass<UTexture2D>("Texture").endClass();

    getGlobalNamespace(L).beginClass<UStaticMesh>("Mesh").endClass();

    getGlobalNamespace(L)
        .deriveClass<UStaticItem, UObject>("StaticItem")
        .addProperty("image", &UStaticItem::get_image, &UStaticItem::set_image)
        .addProperty(
            "max_count",
            &UStaticItem::get_max_count,
            &UStaticItem::set_max_count
        )
        .addProperty(
            "unit_mul", &UStaticItem::get_unit_mul, &UStaticItem::set_unit_mul
        )
        .addProperty("mesh", &UStaticItem::get_mesh, &UStaticItem::set_mesh)
        .endClass();

    getGlobalNamespace(L)
        .deriveClass<URecipe, UObject>("Recipe")
        .addProperty("loss", &URecipe::get_loss, &URecipe::set_loss)
        .addProperty("ticks", &URecipe::get_ticks, &URecipe::set_ticks)
        .endClass();

    getGlobalNamespace(L)
        .deriveClass<URecipeDictionary, UObject>("RecipeDictionary")
        .addStaticFunction("new", &URecipeDictionary::new_object)
        .addFunction("get_recipe", &URecipeDictionary::get_recipe)
        .addFunction("get_count", &URecipeDictionary::get_count)
        .addFunction("add_count", &URecipeDictionary::add_recipe)
        .endClass();
}

int ModLoadingLuaState::AccessorBind(lua_State *l) {
    auto side_acc = Stack<UBaseInventoryAccessor *>::get(l, 1);
    auto container = Stack<UInventoryContainer *>::get(l, 2);

    side_acc->Bind(container);

    return 0;
}

int ModLoadingLuaState::CrafterGetInputContainer(lua_State *l) {
    auto self = Stack<UAutoCrafterBlockLogic *>::get(l, 1);

    std::error_code er;

    push(l, self->mAutoCrafterInputContainer, er);

    return 1;
}

int ModLoadingLuaState::CrafterGetOutputContainer(lua_State *l) {
    auto self = Stack<UAutoCrafterBlockLogic *>::get(l, 1);

    std::error_code er;

    push(l, self->mAutoCrafterOutputContainer, er);

    return 1;
}

int ModLoadingLuaState::AccessorSetSidePos(lua_State *l) {
    auto self = Stack<UBaseInventoryAccessor *>::get(l, 1);
    auto side = Stack<Vec3i>::get(l, 2);
    auto pos = Stack<Vec3i>::get(l, 3);
    self->SetSidePos(side, pos);
    return 0;
}

UClass *ModLoadingLuaState::GetClass(const std::string &name) {
    using namespace std::string_literals;
    auto type = FindObject<UClass>(ANY_PACKAGE, UTF8_TO_TCHAR(name.data()));

    if (type == nullptr) {
        StaticLogger::Get().Log("Class not found " + name);
    }

    return type;
}

void ModLoadingLuaState::RegisterObject(UObject *val) {
    ModLoadingLuaState::Get().mLibrary->RegisterObject(val);
}

inline ModLoadingLuaState &ModLoadingLuaState::Get() {
    static std::unique_ptr<ModLoadingLuaState> inst;

    if (inst == nullptr) {
        inst = std::make_unique<ModLoadingLuaState>();
    }

    return *inst;
}

int ModLoadingLuaState::BlockLogicCreateAccessor(lua_State *l) {
    auto self = Stack<UAutoCrafterBlockLogic *>::get(l, 1);
    auto type = Stack<UClass *>::get(l, 2);
    std::error_code ec;

    if (type && type->IsChildOf(UBaseAccessor::StaticClass())) {
        auto accessor = NewObject<UBaseInventoryAccessor>(self, type);
        self->RegisterComponent(accessor);
        push(l, accessor, ec);
    } else {
        push(l, luabridge::LuaNil(), ec);
    }

    return 1;
}
} // namespace evo