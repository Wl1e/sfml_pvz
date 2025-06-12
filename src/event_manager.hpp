#include <functional>
#include <memory>

namespace demo {

enum EventType
{
    Attack = 0,
    DownHP
};

class Entity;

using eventCallback = std::function<void(Entity*)>;

struct TriggerHandler
{
    std::unordered_map<EventType, eventCallback> handler;
};

using HandlerPtr = std::unique_ptr<TriggerHandler>;

class EventManager
{
public:
    EventManager() = default;
    ~EventManager() = default;

    void registerEvent(Entity*, EventType, eventCallback);
    void trigger(Entity*, EventType);
    void unregisterEvent(Entity*, EventType);
    void clearEvents(Entity*);

private:
    std::unordered_map<Entity*, HandlerPtr> m_handlers;
};

} // namespace demo