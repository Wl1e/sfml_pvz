#include <functional>
#include <memory>

namespace demo {

enum EventType
{
    Attack = 0,
    DownHP
};

class Entity;

using EventCallback = std::function<void(Entity*)>;

void registerEvent(Entity*, EventType, EventCallback);
void trigger(Entity*, EventType);
void unregisterEvent(Entity*, EventType);
void clearEvents(Entity*);

} // namespace demo