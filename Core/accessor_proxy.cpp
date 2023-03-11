#include "accessor_proxy.h"

#include "base_accessor.h"

evo::AccessorProxy::AccessorProxy(EventBus<evo::AccessorEvent> *bus)
    : accessor(nullptr), remove_bus(bus), valid({}) {
    check(bus);
}

evo::AccessorProxy::AccessorProxy(
    UBaseAccessor *our_acc, EventBus<evo::AccessorEvent> *bus
)
    : accessor(our_acc), remove_bus(bus) {
    check(bus);
    check(our_acc);
    valid = bus->subscribe([our_acc, this](const evo::AccessorEvent &event) {
        auto removed_acc = event.data();
        if (removed_acc == our_acc) {
            this->invalidate();
        }
    });
}

evo::AccessorProxy::~AccessorProxy() {
    if (valid) {
        remove_bus->unsubscribe(valid.value());
    }
}

void evo::AccessorProxy::invalidate() {
    valid = {};
    accessor = nullptr;
}