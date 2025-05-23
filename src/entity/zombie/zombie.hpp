#pragma once

#include <entity/entity.hpp>

namespace demo {

struct ZombieData
{
    float HP;
    Direction dir;
    float speed;
    float damage;
    std::string animation;
};

class Zombie : public Entity
{
public:
    explicit Zombie(const ZombieData&, int);

protected:
    void _statusFunction()
    {
    }
};

} // namespace demo