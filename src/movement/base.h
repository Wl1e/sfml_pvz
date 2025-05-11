#pragma once

#include <SFML/System/Vector2.hpp>

namespace demo {

enum class DIRECTION
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

class BaseMovement
{
public:
    constexpr BaseMovement(
        const sf::Vector2f& position = {0, 0},
        DIRECTION dir,
        int speed,
        int acceleration = 0
    ) :
        m_position(position), m_dir(dir), m_speed(speed),
        m_acceleration(acceleration)
    {
    }
    ~BaseMovement();
    void update();
    const sf::Vector2f& getPosition() const
    {
        return m_position;
    }

private:
    sf::Vector2f m_position;
    DIRECTION m_dir;
    int m_speed;
    int m_acceleration;
};

} // namespace demo