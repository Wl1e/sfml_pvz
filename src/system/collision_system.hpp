#pragma once

#include <vector>

#include <system/base.hpp>

namespace demo {

class CollisionSystem : public BaseSystem
{
public:
    CollisionSystem() = default;
    ~CollisionSystem()
    {
        m_entitys.clear();
    }
    void update() override;
    void addEntity(Entity*) override;
    void delEntity(Entity*) override;

private:
    bool _collision(const Entity* const, const Entity* const) const;

private:
    std::vector<std::unordered_set<Entity*>> m_entitys;
};

} // namespace demo