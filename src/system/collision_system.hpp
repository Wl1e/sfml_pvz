#pragma once

#include <vector>

#include <system/base.hpp>

namespace demo {

class CollisionSystem : public BaseSystem
{
public:
    void update() override;
    void addEntity(Entity*) override;
    void delEntity(Entity*) override;

private:
    std::vector<std::unordered_set<Entity*>> m_entitys;
};

} // namespace demo