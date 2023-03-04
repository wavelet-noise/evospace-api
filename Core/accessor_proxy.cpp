#include "accessor_proxy.h"

#include "base_accessor.h"

evo::AccessorProxy::AccessorProxy(UBaseAccessor &a, EventBus &e)
    : accessor(a), eb(e) {
    subscription = e.subscribe<evo::AccessorEvent>(
          events::accessor_removed(),
          [&a, this](const evo::AccessorEvent &eb) {
              auto &acc = eb.data();
              if (&acc == &a) {
                  this->invalidate();
              }
          }
      );
}

evo::AccessorProxy::~AccessorProxy() {
    if (subscription) {
        eb.unsubscribe<evo::AccessorEvent>(subscription.value());
    }
}