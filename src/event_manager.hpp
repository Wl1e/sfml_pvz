#include <any>
#include <functional>
#include <memory>

namespace demo {

enum EventType
{
    Attack = 0,
    DownHP,
    Collide,

    // 和上面算不同类型的Event
    FinishAnimation,

    Click
};

class Entity;

using EventCallback = std::function<void(Entity*, const std::any&)>;

void registerEvent(Entity*, EventType, EventCallback);
void trigger(Entity*, EventType, const std::any&);
void unregisterEvent(Entity*, EventType);
void clearEvents(Entity*);

} // namespace demo