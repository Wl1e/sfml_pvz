#pragma once

#include <entity/components/position_comp.hpp>

namespace demo {

class MovementComp : public PositionComp
{
public:
    MovementComp(
        const sf::Vector2i& pos, const sf::Vector2u& size, int speed
    ) : PositionComp(pos, size), m_speed(speed)
    {
    }

    void update()
    {
        move({0, m_speed});
    }

private:
    int m_speed;
};

} // namespace demo