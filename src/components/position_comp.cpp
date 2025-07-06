#include <components/movement_comp.hpp>
#include <components/position_comp.hpp>
#include <system/collision_system.hpp>
#include <system/init.hpp>
#ifdef DEMO_DEBUG
    #include <animation/gamescene.hpp>
#endif

using namespace std;
using namespace sf;
using namespace demo;

PositionComp::PositionComp(
    RangeType type,
    const PositionType& pos,
    const SizeType& size,
    bool ignoreCollision
) : m_ignoreCollision(ignoreCollision)
{
    if(type == RangeType::Rectangle) {
        m_box = new Range<sf::RectangleShape>(size);
    } else if(type == RangeType::Circle) {
        m_box = new Range<sf::CircleShape>(size);
    } else {
        printf("err shape\n");
    }
    m_box->setPosition(pos);
    setRangeTransplant(m_box, Color::White);
}

PositionComp::~PositionComp()
{
    delete m_box;
}

void PositionComp::update(Entity* entity)
{
    // FIXME: 后续分离出renderComp就替换
#ifdef DEMO_DEBUG
    entity->getScene()->draw(m_box);
#endif
    if(!entity->hasComp(CompType::MOVEMENT)) {
        return;
    }
    move(entity->getComp<CompType::MOVEMENT>()->getMoveValue());
}

PositionType PositionComp::getCenterPos() const
{
    return m_box->getCenterPosition();
}
PositionType PositionComp::getBottomPos() const
{
    return m_box->getBottomPosition();
}

void PositionComp::whenAdd(Entity* entity)
{
    if(m_ignoreCollision) {
        return;
    }
    getSystem("collision")->addEntity(entity);
}

void PositionComp::whenDel(Entity* entity)
{
    getSystem("collision")->delEntity(entity);
}

bool PositionComp::intersection(const PositionComp& pos)
{
    if(m_ignoreCollision || pos.m_ignoreCollision) {
        return false;
    }
    auto targetBox = pos.getBox();
    return isColliding(getBox(), targetBox);
}