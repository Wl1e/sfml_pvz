#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <base/tools.hpp>
#include <entity/defines.hpp>

namespace demo {

class Entity;
class GameScene;

enum class RangeType
{
    Rectangle = 0,
    Circle
};

class BaseRange
{
public:
    virtual RangeType getType() const = 0;
    virtual sf::Shape* getShape() const = 0;
    virtual SizeType getSize() const = 0;
    virtual PositionType getPosition() const = 0;
    virtual PositionType getCenterPosition() const = 0;
    virtual PositionType getBottomPosition() const = 0;
    virtual std::vector<Entity*>
    getEntityInRange(GameScene*, EntityType) = 0;

    virtual void move(const sf::Vector2f&) = 0;
    virtual void setPosition(const PositionType&) = 0;
    virtual void setBottomPosition(const PositionType&) = 0;

    virtual bool inRange(Entity* entity) const = 0;
};

template<class T>
concept ShapeType = std::is_same_v<T, sf::RectangleShape>
                    || std::is_same_v<T, sf::CircleShape>;

template<ShapeType shape>
class Range : public BaseRange
{
public:
    explicit Range(const SizeType&);
    ~Range() = default;

    RangeType getType() const
    {
        return m_type;
    }
    sf::Shape* getShape() const override;
    SizeType getSize() const override;
    PositionType getPosition() const override;
    PositionType getCenterPosition() const override;
    PositionType getBottomPosition() const override;
    std::vector<Entity*>
    getEntityInRange(GameScene*, EntityType) override;

    void setPosition(const PositionType&) override;
    void setBottomPosition(const PositionType&) override;
    void move(const sf::Vector2f& value) override
    {
        m_range->move(value);
    }

    // FIXME
    bool inRange(Entity* entity) const override
    {
        return _inRange(entity);
    }

protected:
    bool _inRange(Entity*) const;

private:
    std::unique_ptr<shape> m_range;
    RangeType m_type;
};

using RectangleRange = Range<sf::RectangleShape>;
using CircleRange = Range<sf::CircleShape>;

bool isColliding(const BaseRange*, const BaseRange*);
void setRangeTransplant(BaseRange*, const sf::Color&);

}; // namespace demo