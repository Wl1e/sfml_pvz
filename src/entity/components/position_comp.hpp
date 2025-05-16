#pragma once

#include <SFML/System/Vector2.hpp>

#include <base/tools.h>
#include <entity/components/component.hpp>
#include <entity/entity.hpp>

// FIXME:
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
    ~PositionComp() = default;

    const sf::Vector2i& getPos() const
    {
        return m_position;
    }
    const sf::Vector2u getSize() const
    {
        return m_size;
    }
    const sf::Vector2i getAxisPos() const
    {
        return axis2pos(getPos());
    }

    void update(Entity* entity) override;
    void move(const sf::Vector2i& move)
    {
        m_position += move;
    }

private:
    sf::Vector2i m_position;
    sf::Vector2u m_size; // 暂时将size放在position内
};

bool overlay(const PositionComp&, const PositionComp&);

} // namespace demo