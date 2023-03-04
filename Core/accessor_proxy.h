#pragma once
#include "Events/block_events.h"

class UBlockLogic;
class UBaseAccessor;

namespace evo {
struct AccessorProxy {
    UBaseAccessor &accessor;
    EventBus &eb;
    std::optional<SubscriptionHandle> subscription;

    AccessorProxy(UBaseAccessor &a, EventBus &e);
    ~AccessorProxy();

    void OnAccessorRemoved(const evo::AccessorEvent &eb) const {}

    void invalidate() { subscription = {}; }
};
} // namespace evo