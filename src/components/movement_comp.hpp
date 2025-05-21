#pragma once

#include <base/direction.hpp>
#include <components/position_comp.hpp>
#include <defines.h>
#include <entity/entity.hpp>

namespace demo {

class Entity;

class MovementComp : public Component
{
public:
    explicit MovementComp(
        Direction dir,
        int speed,
        int acceleration = 0,
        int max_speed = 0
    ) :
        m_dir(dir), m_speed(speed), m_acceleration(acceleration),
        m_max_speed(max_speed)
    {
    }
    ~MovementComp() = default;

    void update(Entity* entity) override
    {
        // 加减速
        if(m_acceleration != 0) {
            if(m_acceleration > 0 && m_speed < m_max_speed) {
                m_speed =
                    std::min(m_speed + m_acceleration, m_max_speed);
            } else if(m_acceleration < 0 && m_speed > m_max_speed) {
                m_speed =
                    std::max(m_speed + m_acceleration, m_max_speed);
            }
        }
    }

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
};

} // namespace demo