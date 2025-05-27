#include <entity/attack.hpp>
#include <entity/plant/plant.hpp>

using namespace std;
using namespace sf;
using namespace demo;

extern unordered_map<EntityStatus, string> animationStatus;
// 后续或许不同植物有不同的偏移，可以改成类变量
static const PositionType PLANT_ATTACK_OFFSET{30, 0};

Plant::Plant(const PlantData& data, const Vector2i& pos) :
    Entity(EntityType::PLANT), m_bullet_type(data.bullet_type)
{
    auto true_pos = axis2pos(pos2axis(PositionType(pos)));
    addComp<CompType::POSITION>(true_pos, data.size);
    addComp<CompType::HP>(data.HP);
    addComp<CompType::ANIMATION>(data.animation);
    addComp<CompType::ATTACK>(
        data.damage,
        data.CD,
        data.range,
        true_pos + PLANT_ATTACK_OFFSET
    );
    getComp<CompType::ATTACK>()->setAttackFunc(plantAttackZombie);
    getComp<CompType::ANIMATION>()->setUpdateInterval(
        data.frame2animation
    );
}

void Plant::_statusFunction()
{
    auto status = getStatus();
    auto animationComp = getComp<CompType::ANIMATION>();
    if(animationComp) {
        animationComp->updateAnimationStatus(
            animationStatus[status]
        );
    }

    if(status == EntityStatus::Died) {
        kill();
    }
}