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
    auto true_pos = axis2pos(pos2axis(PositionType(pos)));

    addComp<CompType::HP>(data.HP);
    addComp<CompType::ANIMATION>(data.animation);

    auto animation = getComp<CompType::ANIMATION>();
    auto animationSize = animation->getAnimationSize();
    if(animationSize.x >= UI_DEFINE::GRASS_LENGTH) {
        animationSize.x = UI_DEFINE::GRASS_LENGTH - 10;
    }
    if(animationSize.y >= UI_DEFINE::GRASS_WIDE) {
        animationSize.y = UI_DEFINE::GRASS_WIDE - 10;
    }
    true_pos -= PositionType(animationSize.componentWiseDiv({2, 1}));
    animation->setUpdateInterval(data.frame2animation);
    animation->setAnimationPos(true_pos);

    addComp<CompType::POSITION>(
        true_pos, SizeType(animationSize.componentWiseDiv({2, 1}))
    );

    auto true_range = new AttackRange(data.range);
    true_range->setPosition(
        getComp<CompType::POSITION>()->getCenterPos()
    );
    addComp<CompType::ATTACK>(data.damage, data.CD, true_range);
    getComp<CompType::ATTACK>()->setAttackFunc(plantAttackZombie);
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