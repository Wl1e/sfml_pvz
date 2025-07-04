#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <base/tools.hpp>

namespace demo {

class GameScene;
class Entity;

// class IBaseAttackRange
// {
// public:
//     virtual ~IBaseAttackRange() = default;
//     virtual void updatePos(const sf::Vector2f&) = 0;
//     virtual bool inRange(Entity*) const = 0;
//     virtual void display(GameScene*) = 0;

//     virtual std::vector<Entity*> getEnemyInRange(Entity*) = 0;

//     virtual Shape* getShape() const = 0;

//     virtual void setPosition(const PositionType& pos);
// };

enum class RangeType
{
    Rectangle = 0,
    Circle
};

class AttackRange
{
public:
    explicit AttackRange(RangeType, const SizeType&);
    AttackRange(const AttackRange&);
    ~AttackRange() = default;

    void updatePos(const sf::Vector2f& move_value)
    {
        m_range->move(move_value);
    }
    void setPosition(const PositionType&);

    void display(GameScene*);
    std::vector<Entity*> getEnemyInRange(Entity*);

    sf::Shape* getShape() const
    {
        return m_range;
    }
    RangeType getRangeType() const
    {
        return m_type;
    }

    PositionType getCenterPos() const;
    // FIXME
    bool inRange(Entity* entity) const
    {
        return _inRange(entity);
    }

protected:
    void _getPos() const
    {
    }
    bool _inRange(Entity*) const;

private:
    RangeType m_type;
    sf::Shape* m_range;
};

}; // namespace demo