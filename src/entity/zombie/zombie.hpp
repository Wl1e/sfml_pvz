#pragma once

#include <entity/entity.hpp>

namespace demo {

struct ZombieData
{
    std::string name;
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

    void _initComp(const ZombieData&, int);
    void _initEvent();
};

} // namespace demo