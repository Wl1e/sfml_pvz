#pragma once

#include <entity/entity.hpp>

namespace demo {

class Zombie : public Entity
{
public:
    explicit Zombie() : Entity(EntityType::ZOMBIE)
    {
    }

    // 比如锤僵尸小游戏
    void click() override
    {
    }

protected:
    void _statusFunction()
    {
    }
};

} // namespace demo