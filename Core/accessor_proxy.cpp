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

evo::AccessorListener::AccessorListener(
    UBaseAccessor *our_acc, EventBus<evo::AccessorEvent> *add,
    EventBus<evo::AccessorEvent> *rem
)
    : opposite_test(our_acc), added_bus(add), removed_bus(rem), proxy(rem) {
    valid =
        added_bus->subscribe([our_acc, this](const evo::AccessorEvent &event) {
            auto added_accessor = event.data();
            auto added_outside = added_accessor->GetOutsideAccessorAny();
            if (our_acc == added_outside) {
                if (our_acc->test_outside(added_outside)) {
                    this->update_proxy(added_accessor);
                }
            }
        });
}

evo::AccessorListener::~AccessorListener(){
    if (valid) {
        added_bus->unsubscribe(valid.value());
    }
}

evo::AccessorListener::AccessorListener(AccessorListener &&l) noexcept
    : opposite_test(l.opposite_test), added_bus(l.added_bus),
      removed_bus(l.removed_bus), valid(l.valid), proxy(l.proxy) {
    l.valid = {}; l.opposite_test = nullptr;
}

void evo::AccessorListener::update_proxy(UBaseAccessor *our_acc) {
    if (!proxy.valid) {
        proxy.valid =
            removed_bus->subscribe([our_acc,
                                    this](const evo::AccessorEvent &event) {
                auto removed_acc = event.data();
                if (removed_acc == our_acc) {
                    proxy.invalidate();
                }
            });
    }

    proxy.accessor = our_acc;
}