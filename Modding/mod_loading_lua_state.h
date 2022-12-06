#pragma once
#include "CoreMinimal.h"
#include "Evospace/CoordinateSystem.h"
#include "lua_state.h"

#include <string>

class UJsonObjectLibrary;
namespace evo {
/**
 * @brief Legacy lua state for BlockLogic lua script part executing
 */
class ModLoadingLuaState : public LuaState {
  public:
    ModLoadingLuaState();

    static int AccessorBind(lua_State *l);

    static int CrafterGetInputContainer(lua_State *l);

    static int CrafterGetOutputContainer(lua_State *l);

    static int AccessorSetSidePos(lua_State *l);
    

    static int BlockLogicCreateAccessor(lua_State *l);
    static UClass *GetClass(const std::string &name);

    static void RegisterObject(UObject *val);

    static ModLoadingLuaState &Get();

  private:
    UJsonObjectLibrary *mLibrary = nullptr;
};
} // namespace evo