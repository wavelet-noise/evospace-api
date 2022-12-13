#include "mod_loading_lua_state.h"

#include "Evospace/Blocks/BaseInventorySideAccessor.h"
#include "Evospace/Item/InventoryContainer.h"
#include "Evospace/JsonObjectLibrary.h"
#include "Evospace/Shared/Core/recipe.h"
#include "Evospace/Shared/Core/recipe_dictionary.h"
#include "Evospace/Shared/Core/static_research.h"

#include <memory>

namespace evo {
ModLoadingLuaState::ModLoadingLuaState() {

    using namespace luabridge;

    getGlobalNamespace(L).addFunction(
        "register", &ModLoadingLuaState::RegisterObject
    );

    getGlobalNamespace(L)
        .beginClass<UInventoryContainer>("InventoryContainer")
        .endClass();

    getGlobalNamespace(L).beginClass<UTexture2D>("Texture").endClass();

    getGlobalNamespace(L).beginClass<UStaticMesh>("Mesh").endClass();

    getGlobalNamespace(L)
        .beginClass<UStaticResearch>("StaticResearch")
        .addProperty("name", &UStaticResearch::name)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<UStaticItem>("StaticItem")
        .addProperty("name", &UStaticItem::name)
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
        .beginClass<URecipe>("Recipe")
        .addProperty("loss", &URecipe::get_loss, &URecipe::set_loss)
        .addProperty("ticks", &URecipe::get_ticks, &URecipe::set_ticks)
        .endClass();

    getGlobalNamespace(L)
        .beginClass<URecipeDictionary>("RecipeDictionary")
        .addProperty("name", &URecipeDictionary::name)
        .addStaticFunction("new", &URecipeDictionary::new_object)
        .addFunction("get_recipe", &URecipeDictionary::get_recipe)
        .addFunction("get_count", &URecipeDictionary::get_count)
        .addFunction("add_count", &URecipeDictionary::add_recipe)
        .endClass();
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
} // namespace evo