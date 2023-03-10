#pragma once

#include "ThirdParty/lua/lua.hpp"

#define LUABRIDGE_MAJOR_VERSION 3
#define LUABRIDGE_MINOR_VERSION 1
#define LUABRIDGE_VERSION 301
#define LUABRIDGE_HAS_EXCEPTIONS 0

#include "detail/CFunctions.h"
#include "detail/ClassInfo.h"
#include "detail/Config.h"
#include "detail/Errors.h"
#include "detail/Expected.h"
#include "detail/FuncTraits.h"
#include "detail/Invoke.h"
#include "detail/Iterator.h"
#include "detail/LuaException.h"
#include "detail/LuaHelpers.h"
#include "detail/LuaRef.h"
#include "detail/Namespace.h"
#include "detail/Overload.h"
#include "detail/Result.h"
#include "detail/ScopeGuard.h"
#include "detail/Security.h"
#include "detail/Stack.h"
#include "detail/TypeTraits.h"
#include "detail/Userdata.h"
