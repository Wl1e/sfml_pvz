#pragma once

#include <SFML/System/Vector2.hpp>

#include <base/direction.hpp>

namespace demo {

class Bullet
{
public:
    explicit Bullet(
        int damage,
        const sf::Vector2i& start,
        Direction dir,
        int range,
        int speed
    );

private:
};

} // namespace demo