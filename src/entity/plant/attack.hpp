#pragma once

#include <entity/plant/plant.hpp>

namespace demo {

class PlantAttack
{
public:
    static void BulletAttack(
        int damage,
        const sf::Vector2i& start,
        const Direction& dir,
        int length,
        int speed
    );
    static void RangeAttack();
};

} // namespace demo