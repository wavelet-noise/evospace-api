#include "accessor_proxy.h"

#include "base_accessor.h"

evo::AccessorProxy::AccessorProxy(UBaseAccessor &acc, EventBus &bus)
    : accessor(acc), bus(bus) {
    subscription = bus.subscribe<evo::AccessorEvent>(
          events::accessor_removed(),
          [&acc, this](const evo::AccessorEvent &event) {
              auto & event_acc = event.data();
              if (&event_acc == &acc) {
                  this->invalidate();
              }
          }
      );
}

evo::AccessorProxy::~AccessorProxy() {
    if (subscription) {
        bus.unsubscribe<evo::AccessorEvent>(subscription.value());
    }
}

void evo::AccessorProxy::invalidate(){ subscription = {}; }