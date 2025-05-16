#pragma once

#include <components/position_comp.hpp>
#include <defines.h>
#include <entity/entity.hpp>

namespace demo {

class Entity;

class MovementComp : public Component
{
public:
    MovementComp(
        direction dir,
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

    sf::Vector2i getMoveValue()
    {
        return mask[static_cast<int>(m_dir)] * m_speed;
    }

private:
    direction m_dir;
    int m_speed;
    int m_acceleration;
    int m_max_speed;

    static sf::Vector2i mask[];
};

} // namespace demo