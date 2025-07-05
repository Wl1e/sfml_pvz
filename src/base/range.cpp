#include <cmath>

#include <base/range.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

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

template<>
bool _isColliding(
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
    const Range<CircleShape>& shape1,
    const Range<RectangleShape>& shape2
)
{
    return _isColliding(shape2, shape1);
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

template<>
Range<RectangleShape>::Range(const SizeType& value) :
    m_range(make_unique<RectangleShape>(value))
{
}

template<>
Range<CircleShape>::Range(const SizeType& value) :
    m_range(make_unique<CircleShape>(value.x))
{
}

template<>
void Range<RectangleShape>::setPosition(const PositionType& pos)
{
    m_range->setPosition(pos);
}
template<>
void Range<CircleShape>::setPosition(const PositionType& pos)
{
    m_range->setPosition(pos - m_range->getGeometricCenter());
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
void Range<CircleShape>::setBottomPosition(const PositionType& pos)
{
    m_range->setPosition(pos - SizeType(0.f, getSize().x));
}

template<ShapeType shape>
std::vector<Entity*> Range<shape>::getEntityInRange(EntityType)
{
}

template<ShapeType shape>
shape* Range<shape>::getShape() const
{
    return m_range.get();
}

template<>
PositionType Range<RectangleShape>::getPosition() const
{
    return m_range->getPosition();
}
template<>
PositionType Range<CircleShape>::getPosition() const
{
    return getCenterPosition();
}

template<ShapeType shape>
PositionType Range<shape>::getCenterPosition() const
{
    return getPosition() + m_range->getGeometricCenter();
}

template<ShapeType shape>
PositionType Range<shape>::getBottomPosition() const
{
    return m_range->getPosition()
           - m_range->getSize().componentWiseDiv({2.f, 1.f});
}

template<>
SizeType Range<RectangleShape>::getSize() const
{
    return m_range->getSize();
}

template<>
SizeType Range<CircleShape>::getSize() const
{
    return SizeType(m_range->getRadius(), 0.);
}

template<>
bool Range<RectangleShape>::_inRange(Entity* entity) const
{
    if(auto position = entity->getComp<CompType::POSITION>();
       position) {
        return m_range->getGlobalBounds()
            .findIntersection(position->getHitbox().getGlobalBounds()
            )
            .has_value();
    }
}

template<ShapeType Shape1>
template<ShapeType Shape2>
bool Range<Shape1>::isColliding(
    const Range<Shape2>& otherRange
) const
{
    // PositionType pos1 = position->getPos();
    // SizeType size1 = position->getSize();
    // PositionType pos2 = m_range->getPosition();
    // SizeType size2 = m_range->getSize();
    // return pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x
    //        && pos1.y < pos2.y + size2.y && pos1.y + size1.y >
    //        pos2.y;
    return _isColliding(*this, otherRange);
}
