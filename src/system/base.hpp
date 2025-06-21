#pragma once

#include <unordered_set>

class Entity;

namespace demo {

class BaseSystem
{
public:
    BaseSystem() = default;
    virtual ~BaseSystem() = 0;

    virtual void update() = 0;
    virtual void addEntity(Entity*);
    virtual void delEntity(Entity*);

private:
    std::unordered_set<Entity*> m_targets;
};

} // namespace demo