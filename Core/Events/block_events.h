#pragma once
#include "event_system.h"

class UBaseAccessor;

namespace evo {
using AccessorEvent = TypedEvent<UBaseAccessor *>;
}

struct events {
    events() = delete;
    static const evo::Name &accessor_removed() {
        static evo::Name name = {"accessor_removed"};
        return name;
    }
    static const evo::Name &accessor_added() {
        static evo::Name name = {"accessor_added"};
        return name;
    }

    static const evo::Name &neighbour_added() {
        static evo::Name name = {"neighbour_added"};
        return name;
    }
    static const evo::Name &neighbour_removed() {
        static evo::Name name = {"neighbour_added"};
        return name;
    }
};