#include <event_manager.hpp>

#include <stdio.h>

using namespace std;
using namespace demo;

struct TriggerHandler
{
    std::unordered_map<EventType, EventCallback> handler;
};

using HandlerPtr = std::unique_ptr<TriggerHandler>;

class EventManager
{
public:
    EventManager() = default;

    ~EventManager() = default;

    inline void registerEvent(Entity*, EventType, EventCallback);
    inline void trigger(Entity*, EventType);
    inline void unregisterEvent(Entity*, EventType);
    inline void clearEvents(Entity*);

private:
    std::unordered_map<Entity*, HandlerPtr> m_handlers;
};

static EventManager _event_manager;

void EventManager::registerEvent(
    Entity* entity, EventType type, EventCallback callback
)
{
    if(m_handlers.find(entity) == m_handlers.end()) {
        m_handlers[entity] = make_unique<TriggerHandler>();
    }
    auto& handler = m_handlers[entity];
    handler->handler[type] = std::move(callback);
}

void EventManager::trigger(Entity* entity, EventType type)
{
    auto handler = m_handlers.find(entity);
    if(handler == m_handlers.end()) {
        return;
    }

    auto callback = handler->second->handler.find(type);
    if(callback == handler->second->handler.end()) {
        return;
    }

    callback->second(entity);
}

void EventManager::unregisterEvent(Entity* entity, EventType type)
{
    if(auto handler = m_handlers.find(entity);
       handler != m_handlers.end()) {
        handler->second->handler.erase(type);
    }
}

void EventManager::clearEvents(Entity* entity)
{
    m_handlers.erase(entity);
}

void demo::registerEvent(
    Entity* entity, EventType type, EventCallback callback
)
{
    // printf("register event entity: %p, type: %d\n", entity, type);
    _event_manager.registerEvent(entity, type, std::move(callback));
}
void demo::trigger(Entity* entity, EventType type)
{
    _event_manager.trigger(entity, type);
}
void demo::unregisterEvent(Entity* entity, EventType type)
{
    // printf("unregister event entity: %p, type: %d\n", entity,
    // type);
    _event_manager.unregisterEvent(entity, type);
}
void demo::clearEvents(Entity* entity)
{
    // printf("clear event entity: %p\n", entity);
    _event_manager.clearEvents(entity);
}