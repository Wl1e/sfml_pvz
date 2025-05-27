#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <base/tools.hpp>

namespace demo {

template<typename T>
    requires sf::CircleShape<T>
class AttackRange
{
public:
    AttackRange()
    {
    }
    virtual ~AttackRange() = 0;

protected:
    void _updatePos(const sf::Vector2f& move_value);
    void _getPos() const
    {
    }

private:
    T m_range;
};

class LineRange : public AttackRange
{
public:
    LineRange();
    ~LineRange();

private:
    sf::RectangleShape m_range;
};

}; // namespace demo