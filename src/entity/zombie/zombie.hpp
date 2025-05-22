#pragma once

#include <entity/entity.hpp>

namespace demo {

struct ZombieData
{
    int HP;
    int speed;
    int Damage;
    std::string animation;
    int path;
};

class Zombie : public Entity
{
public:
    explicit Zombie(const ZombieData&, int path) :
        Entity(EntityType::ZOMBIE)
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