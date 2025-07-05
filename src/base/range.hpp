#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <base/tools.hpp>
#include <entity/defines.hpp>

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

template<class T>
concept ShapeType = std::is_same_v<T, sf::RectangleShape>
                    || std::is_same_v<T, sf::CircleShape>;

template<ShapeType shape>
class Range
{
public:
    explicit Range(const SizeType&);
    ~Range() = default;

    void updatePos(const sf::Vector2f& move_value)
    {
        m_range->move(move_value);
    }
    void setPosition(const PositionType&);
    void setBottomPosition(const PositionType&);

    std::vector<Entity*> getEntityInRange(EntityType);
    shape* getShape() const
    {
        return m_range.get();
    }
    SizeType getSize() const;

    PositionType getPosition() const;
    PositionType getCenterPosition() const;
    PositionType getBottomPosition() const;
    // FIXME
    bool inRange(Entity* entity) const
    {
        return _inRange(entity);
    }
    template<ShapeType otherShape>
    bool isColliding(const Range<otherShape>&) const;

protected:
    bool _inRange(Entity*) const;

private:
    std::unique_ptr<shape> m_range;
};

}; // namespace demo