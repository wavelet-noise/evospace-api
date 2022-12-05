#pragma once
#include "../ThirdParty/result.h"
#include "Evospace/Shared/ThirdParty/luabridge.h"
#include "Evospace/Shared/lua_state_error.h"

#include <string>

struct lua_State;

namespace evo {
class LuaState {
  public:
    static int l_my_print(lua_State *L);

    LuaState();

    void doFile(std::string_view s) { luaL_dofile(L, s.data()); }

    virtual ~LuaState();

    LuaState(const LuaState &) = delete;
    LuaState &operator=(const LuaState &) = delete;

    lua_State *L = nullptr;

    static int ToByteCode_Writer(
        lua_State *L, const void *Ptr, size_t Size, void *UserData
    ) {
        const auto output = static_cast<std::string *>(UserData);
        const auto ptr = static_cast<const uint8_t *>(Ptr);

        output->insert(output->end(), ptr, ptr + Size);
        return 0;
    }

    static auto
    to_byte_code(std::string_view code, std::string_view context) noexcept
        -> result<std::string, std::unique_ptr<AbstractError>>;

    bool RunCode(
        std::string_view Code, std::string_view CodePath = "", int NRet = 0
    ) noexcept;
};
} // namespace evo