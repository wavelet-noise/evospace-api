#pragma once
#include "Events/block_events.h"
#include "Evospace/CoordinateMinimal.h"

class UBlockLogic;
class UBaseAccessor;

namespace evo {
struct AccessorProxy {
    UBaseAccessor *accessor;
    EventBus *bus;

    std::optional<SubscriptionHandle> valid;

    AccessorProxy(EventBus *bus);
    AccessorProxy(UBaseAccessor *our_acc, EventBus *bus);
    ~AccessorProxy();

    void invalidate();
};
struct AccessorListener {
    UBaseAccessor *opposite_test;
    EventBus *bus;

    std::optional<SubscriptionHandle> valid;
    AccessorProxy proxy;

    AccessorListener(UBaseAccessor *our_acc, EventBus *bus);

    void update_proxy(UBaseAccessor *our_acc);
};
} // namespace evo