#pragma once
#include "Events/block_events.h"
#include "Evospace/CoordinateMinimal.h"

class UBlockLogic;
class UBaseAccessor;

namespace evo {
struct AccessorProxy {
    UBaseAccessor *accessor;
    EventBus<evo::AccessorEvent> *remove_bus;

    std::optional<SubscriptionHandle> valid;

    AccessorProxy(EventBus<evo::AccessorEvent> *bus);
    AccessorProxy(UBaseAccessor *our_acc, EventBus<evo::AccessorEvent> *bus);
    ~AccessorProxy();

    void invalidate();
};
} // namespace evo