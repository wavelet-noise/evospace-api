#pragma once

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace evo {
struct Name {
    size_t hash;

    Name(std::string_view name) : hash(std::hash<std::string>{}(name.data())) {
    }

    bool operator==(const Name &other) const { return hash == other.hash; }
};
struct SubscriptionHandle {
    int64 number;
    Name name;
    
    bool operator==(const SubscriptionHandle &other) const { return number == other.number; }
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

class EventBus {
  public:
    using EventCallback = std::function<void(const Event &)>;

    template <typename EventType>
    SubscriptionHandle subscribe(
        Name name, const std::function<void(const EventType &)> &callback
    ) {
        SubscriptionHandle handle = {next_handle++, name};
        m_callbacks[name][handle] = [callback](const Event &event) {
            if constexpr (std::is_same_v<EventType, decltype(event)>) {
                callback(static_cast<const EventType &>(event));
            }
        };
        return handle;
    }

    template <typename EventType>
    void unsubscribe(const SubscriptionHandle &handle) {
        m_callbacks[handle.name].erase(handle);
    }

    template <typename EventType>
    void publish(Name name, const EventType &event) {
        auto typedEvent = TypedEvent<EventType>(event);
        publish(name, typedEvent);
    }

    void publish(Name name, const Event &event) {
        if (!m_callbacks.count(name)) {
            return;
        }
        for (const auto &callback : m_callbacks[name]) {
            callback.second(event);
        }
    }

  private:
    std::unordered_map<
        Name, std::unordered_map<SubscriptionHandle, EventCallback>>
        m_callbacks;
    int64 next_handle = 0;
};
} // namespace evo