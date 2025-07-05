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

// PositionComp::PositionComp(
//     const PositionType& pos,
//     const SizeType& size,
//     bool ignoreCollision
// ) :
//     m_ignoreCollision(ignoreCollision),
//     m_hitbox(sf::RectangleShape(size))
// {
//     m_hitbox.setPosition(pos);

// #ifdef DEMO_DEBUG
//     m_hitbox.setFillColor(sf::Color::Transparent);
//     m_hitbox.setOutlineColor(sf::Color::White);
//     m_hitbox.setOutlineThickness(1);
// #endif
// }

template<ShapeType shape>
PositionComp::PositionComp(
    const PositionType& pos,
    const SizeType& size,
    bool ignoreCollision
) : m_ignoreCollision(ignoreCollision), m_box(Range<shape>(size))
{
    auto trueBox = get<Range<shape>>(m_box);
    trueBox.setPosition(pos);
}

PositionComp::~PositionComp()
{
}

void PositionComp::update(Entity* entity)
{
    // FIXME: 后续分离出renderComp就替换
#ifdef DEMO_DEBUG
    entity->getScene()->draw(m_hitbox);
#endif
    if(!entity->hasComp(CompType::MOVEMENT)) {
        return;
    }
    move(entity->getComp<CompType::MOVEMENT>()->getMoveValue());
}

PositionType PositionComp::getCenterPos() const
{
    return m_hitbox.getPosition() + m_hitbox.getGeometricCenter();
}
PositionType PositionComp::getBottomPos() const
{
    return m_hitbox.getPosition()
           + m_hitbox.getSize().componentWiseDiv({2, 1});
}

void PositionComp::whenAdd(Entity* entity)
{
    getSystem("collision")->addEntity(entity);
}

void PositionComp::whenDel(Entity* entity)
{
    getSystem("collision")->delEntity(entity);
}