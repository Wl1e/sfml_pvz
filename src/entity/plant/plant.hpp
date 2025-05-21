#pragma once

#include <entity/attack.hpp>
#include <entity/entity.hpp>

namespace demo {

struct PlantData
{
    int HP;
    int CD;
    int damage;
    AttackRange range;
    std::string animation;
    SizeType size;
};

class Plant : public Entity
{
public:
    explicit Plant(const PlantData& data, const sf::Vector2i& pos);

    // 比如玉米加农炮
    void click() override
    {
        plantAttackZombie(this);
    }

protected:
    void _statusFunction() override
    {
    }
};

} // namespace demo