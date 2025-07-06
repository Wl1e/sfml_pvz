#include <cmath>

#include <base/range.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

template<ShapeType shape>
vector<Entity*> Range<shape>::getEntityInRange(EntityType type)
{
    return vector<Entity*>();
}

template<ShapeType shape>
Shape* Range<shape>::getShape() const
{
    return m_range.get();
}

template<ShapeType shape>
PositionType Range<shape>::getCenterPosition() const
{
    return m_range->getPosition() + m_range->getGeometricCenter();
}

// ==================RectangleShape==================

template<>
Range<RectangleShape>::Range(const SizeType& value) :
    m_range(make_unique<RectangleShape>(value)),
    m_type(RangeType::Rectangle)
{
}

template<>
SizeType Range<RectangleShape>::getSize() const
{
    return m_range->getSize();
}

template<>
PositionType Range<RectangleShape>::getPosition() const
{
    return m_range->getPosition();
}

template<>
PositionType Range<RectangleShape>::getBottomPosition() const
{
    return m_range->getPosition()
           - getSize().componentWiseDiv({2.f, 1.f});
}

template<>
void Range<RectangleShape>::setPosition(const PositionType& pos)
{
    m_range->setPosition(pos);
}

template<>
void Range<RectangleShape>::setBottomPosition(
    const PositionType& pos
)
{
    m_range->setPosition(
        pos - getSize().componentWiseDiv({2.f, 1.f})
    );
}

template<>
bool Range<RectangleShape>::_inRange(Entity* entity) const
{
    if(auto position = entity->getComp<CompType::POSITION>();
       position) {
        auto pos = position->getBottomPos();
    }
    return false;
}

// ==================CircleShape==================

template<>
Range<CircleShape>::Range(const SizeType& value) :
    m_range(make_unique<CircleShape>(value.x)),
    m_type(RangeType::Circle)
{
}

template<>
SizeType Range<CircleShape>::getSize() const
{
    return SizeType(m_range->getRadius(), 0.);
}

template<>
PositionType Range<CircleShape>::getPosition() const
{
    return getCenterPosition();
}

template<>
PositionType Range<CircleShape>::getBottomPosition() const
{
    return m_range->getPosition() - PositionType(0, getSize().x);
}

template<>
void Range<CircleShape>::setPosition(const PositionType& pos)
{
    m_range->setPosition(pos - m_range->getGeometricCenter());
}

template<>
void Range<CircleShape>::setBottomPosition(const PositionType& pos)
{
    m_range->setPosition(pos - SizeType(0.f, getSize().x));
}

template<>
bool Range<CircleShape>::_inRange(Entity* entity) const
{
    if(auto position = entity->getComp<CompType::POSITION>();
       position) {}
    return false;
}

// ==================isColliding==================

template<ShapeType Shape1, ShapeType Shape2>
bool _isColliding(
    const Range<Shape1>& shape1, const Range<Shape2>& shape2
)
{
    return false;
}

template<>
bool _isColliding(
    const Range<RectangleShape>& shape1,
    const Range<RectangleShape>& shape2
)
{
    PositionType pos1 = shape1.getPosition();
    SizeType size1 = shape1.getSize();
    PositionType pos2 = shape2.getPosition();
    SizeType size2 = shape2.getSize();
    return pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x
           && pos1.y < pos2.y + size2.y && pos1.y + size1.y > pos2.y;
}

bool _RCisColliding(
    const Range<RectangleShape>& shape1,
    const Range<CircleShape>& shape2
)
{
    PositionType pos1 = shape1.getPosition();
    SizeType size1 = shape1.getSize();
    PositionType pos2 = shape2.getPosition();
    float radius = shape2.getSize().x;

    float nearestX =
        std::max(pos1.x, std::min(pos2.x, pos1.x + size1.x));
    float nearestY =
        std::max(pos1.y, std::min(pos2.y, pos1.y + size1.y));

    float deltaX = pos2.x - nearestX;
    float deltaY = pos2.y - nearestY;

    return (deltaX * deltaX + deltaY * deltaY) <= (radius * radius);
}

template<>
bool _isColliding(
    const Range<RectangleShape>& shape1,
    const Range<CircleShape>& shape2
)
{
    return _RCisColliding(shape1, shape2);
}

template<>
bool _isColliding(
    const Range<CircleShape>& shape1,
    const Range<RectangleShape>& shape2
)
{
    return _RCisColliding(shape2, shape1);
}

template<>
bool _isColliding(
    const Range<CircleShape>& shape1,
    const Range<CircleShape>& shape2
)
{
    PositionType pos1 = shape1.getPosition();
    float radius1 = shape1.getSize().x;
    PositionType pos2 = shape2.getPosition();
    float radius2 = shape2.getSize().x;

    return (pos1 - pos2).lengthSquared()
           <= pow(radius1 + radius2, 2);
}

bool isColliding(BaseRange* range1, BaseRange* range2)
{
    auto type1 = range1->getType();
    auto type2 = range2->getType();
    if(type1 == type2) {
        if(type1 == RangeType::Rectangle) {
            return _isColliding(
                *dynamic_cast<RectangleRange*>(range1),
                *dynamic_cast<RectangleRange*>(range2)
            );
        } else if(type1 == RangeType::Circle) {
            return _isColliding(
                *dynamic_cast<CircleRange*>(range1),
                *dynamic_cast<CircleRange*>(range2)
            );
        }
    } else if(type1 == RangeType::Rectangle
              && type2 == RangeType::Circle) {
        return _isColliding(
            *dynamic_cast<RectangleRange*>(range1),
            *dynamic_cast<CircleRange*>(range2)
        );
    } else if(type1 == RangeType::Circle
              && type2 == RangeType::Rectangle) {
        return _isColliding(
            *dynamic_cast<CircleRange*>(range1),
            *dynamic_cast<RectangleRange*>(range2)
        );
    }
    return false;
}