#pragma once

#include <entity/entity.hpp>

namespace demo {

struct ZombieData
{
    float HP;
    SizeType size;

    // move
    Direction dir;
    float speed;

    // animation
    std::string animation;
    int frame2animation;

    // attack
    float CD;
    float damage;
};

class Zombie : public Entity
{
public:
    explicit Zombie(const ZombieData&, int);
    ~Zombie() = default;

protected:
    void _statusFunction();
};

} // namespace demo