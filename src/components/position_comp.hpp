#pragma once

#include <SFML/System/Vector2.hpp>

#include <base/range.hpp>
#include <base/tools.hpp>
#include <components/component.hpp>
#include <entity/entity.hpp>

namespace demo {

// 兼顾position和hitbox
class PositionComp : public Component
{
public:
    // explicit PositionComp(
    //     const PositionType&, const SizeType&, bool = false
    // );
    explicit PositionComp(
        RangeType, const PositionType&, const SizeType&, bool = false
    );
    ~PositionComp();

    // 要不然position和size都改成Vector2f得了
    PositionType getPos() const
    {
        return m_box->getPosition();
    }
    SizeType getSize() const
    {
        return m_box->getSize();
    }
    sf::Vector2i getAxisPos() const
    {
        return pos2axis(getPos());
    }
    const BaseRange* const getBox() const
    {
        return m_box;
    }
    PositionType getCenterPos() const;
    PositionType getBottomPos() const;

    bool isIgnoreCollision() const
    {
        return m_ignoreCollision;
    }

    void update(Entity* entity) override;
    void move(const sf::Vector2f& value)
    {
        m_box->move(value);
    }
    void setIgnoreCollision(bool ignoreCollision)
    {
        m_ignoreCollision = ignoreCollision;
    }
    void setPosition(const PositionType& pos)
    {
        m_box->setPosition(pos);
    }

    bool intersection(const PositionComp& pos)
    {
        if(m_ignoreCollision || pos.m_ignoreCollision) {
            return false;
        }
        auto targetBox = pos.getBox();
        // if(isColliding(getBox(), targetBox)) {}
        // return m_hitbox.getGlobalBounds()
        //     .findIntersection(pos.m_hitbox.getGlobalBounds())
        //     .has_value();
        return false;
    }
    bool clicked(const PositionType& clickPos)
    {
        return m_hitbox.getGlobalBounds().contains(clickPos);
    }

    void whenAdd(Entity*) override;
    void whenDel(Entity*) override;

private:
    bool m_ignoreCollision;
    sf::RectangleShape m_hitbox;

    BaseRange* m_box;
};

// bool overlay(const PositionComp&, const PositionComp&);

} // namespace demo