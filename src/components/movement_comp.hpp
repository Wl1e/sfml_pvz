#pragma once

#include <base/direction.hpp>
#include <components/position_comp.hpp>
#include <defines.h>

namespace demo {

class Entity;

class MovementComp : public Component
{
public:
    explicit MovementComp(
        Direction dir,
        int speed,
        int max_distance,
        int acceleration = 0,
        int max_speed = 0
    ) :
        m_dir(dir), m_speed(speed), m_acceleration(acceleration),
        m_max_speed(max_speed), m_distance(max_distance)
    {
    }
    ~MovementComp() = default;

    void update(Entity*) override;

    void setDir(const Direction& dir)
    {
        m_dir = dir;
    }

    sf::Vector2f getMoveValue()
    {
        return m_dir.getOffset() * m_speed;
    }

private:
    Direction m_dir;
    float m_speed;
    int m_acceleration;
    float m_max_speed;

    int m_distance;
};

} // namespace demo