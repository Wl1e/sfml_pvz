#pragma once

#include <entity/plant/plant.hpp>

namespace demo {

class PlantAttack
{
public:
    static void BulletAttack(
        int damage, const sf::Vector2i& start, int range, int speed
    );
    static void RangeAttack();
};

} // namespace demo