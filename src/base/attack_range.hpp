#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <base/tools.hpp>

namespace demo {

class GameScene;
class Entity;

sf::RectangleShape rs;
void f()
{
}

template<typename T>
class AttackRange
{
public:
    AttackRange(T shape) : m_range(std::move(shape))
    {
        static_assert(
            std::is_same_v<T, sf::RectangleShape>
                || std::is_same_v<T, sf::CircleShape>,
            "range only supports Circle and Rectangle"
        );
    }
    virtual ~AttackRange() = 0;

    void updatePos(const sf::Vector2f& move_value)
    {
        m_range.move(move_value);
    }

    void display(GameScene*);
    std::vector<Entity*> getEnemyInRange(Entity*);
    const T& getAttackRange() const
    {
        returm m_range;
    }
    // FIXME
    bool inRange(Entity* entity) const
    {
        _inRange(entity);
    }

protected:
    void _getPos() const
    {
    }
    bool _inRange(Entity*) const;

private:
    T m_range;
};

using RectangleAttackRange = AttackRange<sf::RectangleShape>;
using CircleAttackRange = AttackRange<sf::CircleShape>;

}; // namespace demo