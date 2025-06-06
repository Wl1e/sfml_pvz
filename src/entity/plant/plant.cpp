#include <base/attack_range.hpp>
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

    addComp<CompType::ANIMATION>(data.animation);

    auto animationSize =
        getComp<CompType::ANIMATION>()->getAnimationSize();
    true_pos -= PositionType(animationSize.componentWiseDiv({2, 1}));
    addComp<CompType::POSITION>(true_pos, SizeType(animationSize));
    addComp<CompType::HP>(data.HP);

    auto true_range = new AttackRange(data.range);
    true_range->setPosition(true_pos);
    addComp<CompType::ATTACK>(data.damage, data.CD, true_range);
    getComp<CompType::ATTACK>()->setAttackFunc(plantAttackZombie);

    auto animation = getComp<CompType::ANIMATION>();
    animation->setUpdateInterval(data.frame2animation);
    animation->setAnimationPos(true_pos);
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