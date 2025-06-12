#include <event_manager.hpp>

using namespace std;
using namespace demo;

void EventManager::registerEvent(
    Entity* entity, EventType type, eventCallback callback
)
{
    auto& handler = m_handlers[entity];
    if(!handler) {
        m_handlers[entity] = make_unique<TriggerHandler>();
    }
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