#include <components/movement_comp.hpp>
#include <components/position_comp.hpp>
#ifdef DEMO_DEBUG
    #include <animation/gamescene.hpp>
#endif

using namespace std;
using namespace sf;
using namespace demo;

// bool demo::overlay(
//     const PositionComp& pos1, const PositionComp& pos2
// )
// {
//     if(pos1.isIgnoreCollision() || pos2.isIgnoreCollision()) {
//         return false;
//     }
//     auto leftTop1 = pos1.getPos();
//     auto rightDown1 = leftTop1 + pos1.getSize();
//     auto leftTop2 = pos2.getPos();
//     auto rightDown2 = leftTop2 + pos2.getSize();

//     return !(
//         rightDown1.x < leftTop2.x || leftTop1.x > rightDown2.x
//         || rightDown1.y < leftTop2.y || leftTop1.y > rightDown2.y
//     );
// }

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
