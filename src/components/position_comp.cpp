#include <components/movement_comp.hpp>
#include <components/position_comp.hpp>

using namespace std;
using namespace sf;
using namespace demo;

bool demo::overlay(
    const PositionComp& pos1, const PositionComp& pos2
)
{
    auto& leftTop1 = pos1.getPos();
    auto rightDown1 = leftTop1 + Vector2i(pos1.getSize());
    auto& leftTop2 = pos2.getPos();
    auto rightDown2 = leftTop2 + Vector2i(pos2.getSize());

    return !(
        rightDown1.x < leftTop2.x || leftTop1.x > rightDown2.x
        || rightDown1.y < leftTop2.y || leftTop1.y > rightDown2.y
    );
}

void PositionComp::update(Entity* entity)
{
    updateCollision(entity);
    updateMove(entity);
}

void PositionComp::updateCollision(Entity* entity)
{
}

void PositionComp::updateMove(Entity* entity)
{
    auto component = entity->getComp(CompType::MOVEMENT);
    if(!component) {
        return;
    }
    auto movement =
        castToComp<type2cls<CompType::MOVEMENT>::type>(component);

    move(movement->getMoveValue());
}