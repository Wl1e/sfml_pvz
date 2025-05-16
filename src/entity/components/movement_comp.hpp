#pragma once

#include <defines.h>
#include <entity/components/position_comp.hpp>
#include <entity/entity.hpp>

namespace demo {

class Entity;

// FIXME: movement可以只包含方向和速度
class MovementComp : public Component
{
public:
    MovementComp(direction dir, int speed) :
        m_dir(dir), m_speed(speed)
    {
    }
    ~MovementComp() = default;

    void update(Entity* entity) override
    {
        // FIXME: update m_dir or m_speed
    }

    sf::Vector2i getMoveValue()
    {
        return mask[static_cast<int>(m_dir)] * m_speed;
    }

private:
    direction m_dir;
    int m_speed;

    static sf::Vector2i mask[];
};

} // namespace demo