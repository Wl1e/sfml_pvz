#pragma once

#include <SFML/System/Vector2.hpp>

#include <base/tools.h>
#include <entity/components/component.hpp>

namespace demo {
class PositionComp : public Component
{
public:
    PositionComp(
        const sf::Vector2i& pos, bool axis, const sf::Vector2u& size
    ) : m_size(size)
    {
        if(axis) {
            m_axis_position = pos;
            m_position = axis2pos(m_axis_position);
        } else {
            m_position = pos;
            m_axis_position = pos2axis(m_position);
        }
    }

    const sf::Vector2i& getPos() const
    {
        return m_position;
    }
    const sf::Vector2i& getAxisPos() const
    {
        return m_axis_position;
    }
    const sf::Vector2u getSize() const
    {
        return m_size;
    }

    void update(const sf::Vector2i& move)
    {
        m_position += move;
        auto newAxisPos = pos2axis(m_position);
        if(newAxisPos != m_axis_position) {
            m_axis_position = newAxisPos;
        }
    }

private:
    sf::Vector2i m_position;
    sf::Vector2i m_axis_position;
    sf::Vector2u m_size; // 暂时将size放在position内
};

bool overlay(const PositionComp&, const PositionComp&);

} // namespace demo