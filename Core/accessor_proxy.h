#pragma once
#include "Events/block_events.h"

class UBlockLogic;
class UBaseAccessor;

namespace evo {
struct AccessorProxy {
    UBaseAccessor &accessor;
    EventBus &bus;
    
    std::optional<SubscriptionHandle> subscription;

    AccessorProxy(UBaseAccessor &acc, EventBus &bus);
    ~AccessorProxy();

    void invalidate() ;
};
} // namespace evo