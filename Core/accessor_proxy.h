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
struct AccessorListener {
    UBaseAccessor *opposite_test;
    EventBus<evo::AccessorEvent> *added_bus;
    EventBus<evo::AccessorEvent> *removed_bus;

    std::optional<SubscriptionHandle> valid;
    AccessorProxy proxy;

    AccessorListener(
        UBaseAccessor *our_acc, EventBus<evo::AccessorEvent> *add,
        EventBus<evo::AccessorEvent> *rem
    );

    ~AccessorListener();

    AccessorListener(const AccessorListener &l) = delete;

    AccessorListener(AccessorListener &&l) noexcept;

    void update_proxy(UBaseAccessor *our_acc);
};
} // namespace evo