#include <entity/plant/plant.hpp>

using namespace std;
using namespace sf;
using namespace demo;

// 后续或许不同植物有不同的偏移，可以改成类变量
static const PositionType PLANT_ATTACK_OFFSET{10, 0};

Plant::Plant(const PlantData& data, const Vector2i& pos) :
    Entity(EntityType::PLANT)
{
    addComp<CompType::POSITION>(PositionType(pos), data.size);
    addComp<CompType::HP>(data.HP);
    addComp<CompType::ANIMATION>(data.animation);
    addComp<CompType::ATTACK>(
        data.damage,
        data.CD,
        data.range,
        getComp<CompType::POSITION>()->getPos() + PLANT_ATTACK_OFFSET
    );
    getComp<CompType::ATTACK>()->setAttackFunc(plantAttackZombie);
    getComp<CompType::ATTACK>()->setBanAttack(true);
}