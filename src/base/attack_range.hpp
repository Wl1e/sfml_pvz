#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <base/tools.hpp>

namespace demo {

class GameScene;
class Entity;

class IBaseAttackRange
{
public:
    virtual ~IBaseAttackRange() = default;
    virtual void updatePos(const sf::Vector2f& move_value) = 0;
    virtual bool inRange(Entity* entity) const = 0;
    virtual void display(GameScene*) = 0;

    virtual std::vector<Entity*> getEnemyInRange(Entity*) = 0;
    virtual float getRotationDegrees() const = 0;
    virtual const PositionType& getPosition() const = 0;

    virtual void setPosition(const PositionType& pos);
};

template<typename T>
class AttackRange : public IBaseAttackRange
{
public:
    AttackRange(T shape) : m_range(std::move(shape))
    {
        static_assert(
            std::is_same_v<T, sf::RectangleShape>
                || std::is_same_v<T, sf::CircleShape>,
            "range only supports Circle and Rectangle"
        );

#ifdef DEMO_DEBUG
        m_range->setFillColor(sf::Color::Transparent);
        m_range->setOutlineColor(sf::Color::Red);
        m_range->setOutlineThickness(1);
#endif
    }
    virtual ~AttackRange() = default;

    void updatePos(const sf::Vector2f& move_value) override
    {
        m_range.move(move_value);
    }
    void setPosition(const PositionType& pos) override
    {
        m_range.setPosition(pos);
    }

    void display(GameScene*) override;
    std::vector<Entity*> getEnemyInRange(Entity*) override;
    const T& getAttackRange() const override
    {
        returm m_range;
    }
    float getRotationDegrees() const
    {
        m_range.getRotation().asDegrees();
    }
    const PositionType& getPosition() const
    {
        return m_range.getPosition();
    }
    // FIXME
    bool inRange(Entity* entity) const override
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