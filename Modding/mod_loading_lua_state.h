#pragma once
#include "CoreMinimal.h"
#include "Evospace/CoordinateSystem.h"
#include "lua_state.h"

#include <string>

class UJsonObjectLibrary;
namespace evo {
class ModLoadingLuaState : public LuaState {
  public:
    ModLoadingLuaState();

    static int AccessorBind(lua_State *l);

    static int CrafterGetInputContainer(lua_State *l);

    static int CrafterGetOutputContainer(lua_State *l);

    static int AccessorSetSidePos(lua_State *l);

    static int NewVec3i(lua_State *l);

    static int ZeroVec3i(lua_State *l);
    static int OneVec3i(lua_State *l);
    static int UpVec3i(lua_State *l);
    static int DownVec3i(lua_State *l);
    static int LeftVec3i(lua_State *l);
    static int RightVec3i(lua_State *l);
    static int BackVec3i(lua_State *l);
    static int FrontVec3i(lua_State *l);

    static int BlockLogicCreateAccessor(lua_State *l);
    static UClass *GetClass(const std::string &name);

    static void RegisterObject(UObject *val);

    static ModLoadingLuaState &Get();

  private:
    UJsonObjectLibrary *mLibrary = nullptr;
};
} // namespace evo