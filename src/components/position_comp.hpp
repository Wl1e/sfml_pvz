#pragma once

#include <SFML/System/Vector2.hpp>

#include <base/tools.h>
#include <components/component.hpp>
#include <entity/entity.hpp>

namespace demo {

class PositionComp : public Component
{
public:
    explicit PositionComp(
        const sf::Vector2i& pos,
        const sf::Vector2u& size = {0, 0},
        bool ignoreCollision = false
    ) :
        m_position(pos), m_size(size),
        m_ignoreCollision(ignoreCollision)
    {
    }
    ~PositionComp() = default;

    const sf::Vector2i& getPos() const
    {
        return m_position;
    }
    const sf::Vector2u& getSize() const
    {
        return m_size;
    }
    sf::Vector2i getAxisPos() const
    {
        return axis2pos(getPos());
    }
    // sf::Vector2i getCenterPos()
    // {
    //     return getPos() + (getSize() / 2);
    // }
    bool isIgnoreCollision() const
    {
        return m_ignoreCollision;
    }

    void update(Entity* entity) override;
    void move(const sf::Vector2i& move)
    {
        m_position += move;
    }

    static bool overlay(const PositionComp&, const PositionComp&);

private:
    void updateCollision(Entity*);
    void updateMove(Entity*);

private:
    sf::Vector2i m_position;
    sf::Vector2u m_size; // 暂时将size放在position内

    bool m_ignoreCollision;
};

} // namespace demo