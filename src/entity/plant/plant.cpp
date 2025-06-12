#include <base/attack_range.hpp>
#include <entity/attack.hpp>
#include <entity/plant/plant.hpp>
#include <UI/defines.hpp>

using namespace std;
using namespace sf;
using namespace demo;

extern unordered_map<EntityStatus, string> animationStatus;
// 后续或许不同植物有不同的偏移，可以改成类变量
static const PositionType PLANT_ATTACK_OFFSET{30, 0};

Plant::Plant(const PlantData& data, const Vector2i& pos) :
    Entity(EntityType::PLANT), m_bullet_type(data.bullet_type)
{
    init(data, pos);
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

void Plant::init(const PlantData& data, const Vector2i& pos)
{
    auto true_pos = axis2pos(pos2axis(PositionType(pos)));

    addComp<CompType::HP>(data.HP);
    addComp<CompType::ANIMATION>(data.animation);

    auto animation = getComp<CompType::ANIMATION>();
    animation->setUpdateInterval(data.frame2animation);

    auto trueSize = fitableSize(animation->getAnimationSize());
    true_pos -= PositionType(trueSize.componentWiseDiv({2, 1}));
    animation->setAnimationPos(true_pos);

    addComp<CompType::POSITION>(
        true_pos, SizeType(trueSize.componentWiseDiv({2, 1}))
    );

    auto true_range = new AttackRange(data.range);
    true_range->setPosition(
        getComp<CompType::POSITION>()->getCenterPos()
    );
    addComp<CompType::ATTACK>(data.damage, data.CD, true_range);
    getComp<CompType::ATTACK>()->setAttackFunc(plantAttackZombie);
}