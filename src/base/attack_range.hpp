#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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

enum class rangeType
{
    Rectangle = 0,
    Circle
};

class AttackRange
{
public:
    AttackRange(rangeType type, const SizeType& size) :
        m_type(type), m_range(nullptr)
    {
        if(m_type == rangeType::Rectangle) {
            m_range = new sf::RectangleShape(size);
        } else if(m_type == rangeType::Circle) {
            m_range = new sf::CircleShape(size.x);
        } else {
            // err
        }

#ifdef DEMO_DEBUG
        if(m_range) {
            m_range->setFillColor(sf::Color::Transparent);
            m_range->setOutlineColor(sf::Color::Red);
            m_range->setOutlineThickness(1);
        }
#endif
    }
    ~AttackRange() = default;

    void updatePos(const sf::Vector2f& move_value)
    {
        m_range->move(move_value);
    }
    void setPosition(const PositionType& pos)
    {
        m_range->setPosition(pos);
    }

    void display(GameScene*);
    std::vector<Entity*> getEnemyInRange(Entity*);

    sf::RectangleShape* getRectangleShape() const
    {
        if(m_type == rangeType::Rectangle) {
            return static_cast<sf::RectangleShape*>(m_range);
        }
        return nullptr;
    }

    const sf::CircleShape* getCircleShape() const
    {
        if(m_type == rangeType::Circle) {
            return static_cast<sf::CircleShape*>(m_range);
        }
        return nullptr;
    }
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
    rangeType m_type;
    Shape* m_range;
};

}; // namespace demo