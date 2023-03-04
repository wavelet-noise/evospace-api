#include "accessor_proxy.h"

#include "base_accessor.h"

evo::AccessorProxy::AccessorProxy(EventBus *bus)
    : accessor(nullptr), bus(bus), valid({}) {}

evo::AccessorProxy::AccessorProxy(UBaseAccessor *our_acc, EventBus *bus)
    : accessor(our_acc), bus(bus) {
    valid = bus->subscribe<evo::AccessorEvent>(
        events::accessor_removed(),
        [&our_acc, this](const evo::AccessorEvent &event) {
            auto removed_acc = event.data();
            if (removed_acc == our_acc) {
                this->invalidate();
            }
        }
    );
}

evo::AccessorProxy::~AccessorProxy() {
    if (valid) {
        bus->unsubscribe<evo::AccessorEvent>(valid.value());
    }
}

void evo::AccessorProxy::invalidate() { valid = {}; accessor = nullptr; }

evo::AccessorListener::AccessorListener(UBaseAccessor *our_acc, EventBus *bus)
    : opposite_test(our_acc), bus(bus) {
    valid = bus->subscribe<evo::AccessorEvent>(
        events::accessor_added(),
        [&our_acc, this](const evo::AccessorEvent &event) {
            auto added_accessor = event.data();
            auto added_outside = added_accessor->GetOutsideAccessor();
            if (our_acc == added_outside && our_acc->test_outside(added_outside)) {
                this->update_proxy(added_accessor);
            }
        }
    );
}

void evo::AccessorListener::update_proxy(UBaseAccessor *our_acc) {
    if (!proxy.valid) {
        proxy.valid = bus->subscribe<evo::AccessorEvent>(
        events::accessor_removed(),
        [&our_acc, this](const evo::AccessorEvent &event) {
                auto removed_acc = event.data();
                if (removed_acc == our_acc) {
                    proxy.invalidate();
                }
            }
        );
    }

    proxy.accessor = our_acc;
}