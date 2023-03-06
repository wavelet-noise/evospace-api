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

    SubscriptionHandle subscribe(const EventCallback &callback) {
        return m_callbacks.emplace(SubscriptionHandle{next_handle++}, callback)
            .first->first;
    }

    void unsubscribe(const SubscriptionHandle &handle) {
        if (alive) {
            m_callbacks.erase(handle);
        }
    }

    void publish(const EventType &event) {
        if (!m_callbacks.size()) {
            return;
        }
        for (const auto &callback : m_callbacks) {
            callback.second(event);
        }
    }

    void clear() {
        alive = false;
        m_callbacks = {};
    }

  private:
    std::unordered_map<SubscriptionHandle, EventCallback> m_callbacks = {};
    int64 next_handle = 0;
    bool alive = true;
};
} // namespace evo