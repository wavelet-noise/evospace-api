#pragma once
#include "event_system.h"

class UBaseAccessor;

namespace evo {
using AccessorEvent = TypedEvent<UBaseAccessor>;
}

namespace events {
inline const evo::Name &accessor_removed() {
    static evo::Name name = {"accessor_removed"};
    return name;
}
inline const evo::Name &accessor_added() {
    static evo::Name name = {"accessor_added"};
    return name;
}

inline const evo::Name &neighbour_added() {
    static evo::Name name = {"neighbour_added"};
    return name;
}
inline const evo::Name &neighbour_removed() {
    static evo::Name name = {"neighbour_added"};
    return name;
}
} // namespace events