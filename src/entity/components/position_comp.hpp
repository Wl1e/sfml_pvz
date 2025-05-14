#pragma once

#include <SFML/System/Vector2.hpp>

#include <base/tools.h>
#include <entity/components/component.hpp>

// fixme:
// 我搞错了，要分成不可移动的和可移动的，目前的position都是不可移动的

namespace demo {

class PositionComp : public Component
{
public:
    PositionComp(
        const sf::Vector2i& pos, const sf::Vector2u& size = {0, 0}
    ) : m_position(pos), m_size(size)
    {
    }

    const sf::Vector2i& getPos() const
    {
        return m_position;
    }
    const sf::Vector2u getSize() const
    {
        return m_size;
    }

    void update() override
    {
        // m_position += move;
    }
    void move(const sf::Vector2i& move)
    {
        m_position += move;
    }
    void whenAdded(Entity*) override
    {
    }

private:
    sf::Vector2i m_position;
    sf::Vector2u m_size; // 暂时将size放在position内
};

class AxisPositionComp : public Component
{
public:
    AxisPositionComp(
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

    void update() override
    {
        // m_position += move;
        // auto newAxisPos = pos2axis(m_position);
        // if(newAxisPos != m_axis_position) {
        //     m_axis_position = newAxisPos;
        // }
    }

    void whenAdded(Entity*) override
    {
    }

private:
    sf::Vector2i m_position;
    sf::Vector2i m_axis_position;
    sf::Vector2u m_size; // 暂时将size放在position内
};

bool overlay(const PositionComp&, const PositionComp&);

} // namespace demo