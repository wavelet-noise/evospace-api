#pragma once

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace evo {
struct Name {
    size_t hash;

    Name(std::string_view name) : hash(std::hash<std::string>{}(name.data())) {}

    bool operator==(const Name &other) const { return hash == other.hash; }
};
struct SubscriptionHandle {
    int64 number;

    bool operator==(const SubscriptionHandle &other) const {
        return number == other.number;
    }
};
} // namespace evo

namespace std {
template <> struct hash<evo::Name> {
    size_t operator()(const evo::Name &key) const noexcept { return key.hash; }
};
template <> struct hash<evo::SubscriptionHandle> {
    size_t operator()(const evo::SubscriptionHandle &key) const noexcept {
        return std::hash<int64>{}(key.number);
    }
};
} // namespace std

class Event {
  public:
    virtual ~Event() {}
};

namespace evo {
template <typename EventType> class TypedEvent : public Event {
  public:
    TypedEvent(const EventType &data) : m_data(data) {}
    const EventType &data() const { return m_data; }

  private:
    EventType m_data;
};

class EventSystem {
  public:
};

template <typename EventType> class EventBus {
  public:
    using EventCallback = std::function<void(const EventType &)>;

    SubscriptionHandle
    subscribe(const std::function<void(const EventType &)> &callback) {
        SubscriptionHandle handle = {next_handle++};
        m_callbacks[handle.number] = callback;
        return handle;
    }

    void unsubscribe(const SubscriptionHandle &handle) {
        m_callbacks.erase(handle.number);
    }

    void publish(const EventType &event) {
        if (!m_callbacks.size()) {
            return;
        }
        for (const auto &callback : m_callbacks) {
            callback.second(event);
        }
    }

  private:
    std::unordered_map<int64, EventCallback> m_callbacks = {};
    int64 next_handle = 0;
};
} // namespace evo