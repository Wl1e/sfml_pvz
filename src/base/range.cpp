#include <cmath>

#include <animation/gamescene.hpp>
#include <base/range.hpp>
#include <defines.hpp>
#include <entity/entity.hpp>
#include <entity/zombie/zombie.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void demo::setRangeTransplant(
    BaseRange* m_box, const sf::Color& color
)
{
    auto shape = m_box->getShape();
    shape->setFillColor(sf::Color::Transparent);
    shape->setOutlineColor(color);
    shape->setOutlineThickness(1);
}

#define VEC_OPERATOR(opt)                                          \
    bool operator opt(const Vector2f& left, const Vector2f& right) \
    {                                                              \
        return left.x opt right.x && left.y opt right.y;           \
    }

VEC_OPERATOR(<=)
VEC_OPERATOR(<)
VEC_OPERATOR(>)

// FIXME: Circle其实不通用
template<ShapeType shape>
vector<Entity*>
Range<shape>::getEntityInRange(GameScene* scene, EntityType type)
{
    vector<Entity*> res;
    // 单线攻击优化
    int path = getPath(getBottomPosition());
    if(type == EntityType::PLANT) {
        auto plant = scene->getPlantByAxis(
            Vector2i(pos2axis(getBottomPosition()))
        );
        if(plant) {
            res.push_back((Entity*)plant);
        }
    } else if(type == EntityType::ZOMBIE) {
        // FIXME:
        // 这里的判断直接导致需要引用entity/zombie，依赖关系过于杂乱
        auto bounds = getShape()->getGlobalBounds();
        for(auto zombie : scene->getZombiesByPath(path)) {
            // 这里过于暴露底层逻辑
            if(bounds
                   .findIntersection(
                       zombie->getComp<CompType::POSITION>()
                           ->getBox()
                           ->getShape()
                           ->getGlobalBounds()
                   )
                   .has_value()) {
                res.push_back(zombie);
            }
        }
    }
    return res;
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
           + getSize().componentWiseDiv({2.f, 1.f});
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
    auto position = entity->getComp<CompType::POSITION>();
    if(!position) {
        return false;
    }

    auto targetPos = position->getBottomPos();
    PositionType pos = getPosition();
    if(targetPos < pos) {
        return false;
    }
    if(targetPos - pos > getSize()) {
        return false;
    }
    return true;
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
    auto position = entity->getComp<CompType::POSITION>();
    if(!position) {
        return false;
    }

    auto targetPos = position->getBottomPos();
    PositionType pos = getPosition();
    if((targetPos - pos).lengthSquared()
       > getSize().lengthSquared()) {
        return false;
    }
    return true;
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

bool demo::isColliding(
    const BaseRange* range1, const BaseRange* range2
)
{
    auto type1 = range1->getType();
    auto type2 = range2->getType();
    if(type1 == type2) {
        if(type1 == RangeType::Rectangle) {
            return _isColliding(
                *dynamic_cast<const RectangleRange*>(range1),
                *dynamic_cast<const RectangleRange*>(range2)
            );
        } else if(type1 == RangeType::Circle) {
            return _isColliding(
                *dynamic_cast<const CircleRange*>(range1),
                *dynamic_cast<const CircleRange*>(range2)
            );
        }
    } else if(type1 == RangeType::Rectangle
              && type2 == RangeType::Circle) {
        return _isColliding(
            *dynamic_cast<const RectangleRange*>(range1),
            *dynamic_cast<const CircleRange*>(range2)
        );
    } else if(type1 == RangeType::Circle
              && type2 == RangeType::Rectangle) {
        return _isColliding(
            *dynamic_cast<const CircleRange*>(range1),
            *dynamic_cast<const RectangleRange*>(range2)
        );
    }
    return false;
}
