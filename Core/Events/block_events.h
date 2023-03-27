#pragma once
#include "event_system.h"

class ADimension;
class UBaseAccessor;

namespace evo {
using AccessorEvent = TypedEvent<UBaseAccessor *>;
using DimensionLoadedEvent = TypedEvent<ADimension *>;
}