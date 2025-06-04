#include <base/attack_range.hpp>
#include <entity/attack.hpp>
#include <entity/zombie/zombie.hpp>
#include <UI/defines.hpp>

using namespace std;
using namespace sf;
using namespace demo;

extern unordered_map<EntityStatus, string> animationStatus;

Zombie::Zombie(const ZombieData& data, int path) :
    Entity(EntityType::ZOMBIE)
{
    auto true_pos = axis2pos({UI_DEFINE::GRASS_COUNT - 1, path});

    addComp<CompType::MOVEMENT>(data.dir, data.speed, 999);
    addComp<CompType::ANIMATION>(data.animation);

    auto animation = getComp<CompType::ANIMATION>();
    auto animationSize = animation->getAnimationSize();

    true_pos -= PositionType(animationSize.componentWiseDiv({2, 1}));
    addComp<CompType::POSITION>(true_pos, SizeType(animationSize));

    animation->setUpdateInterval(data.frame2animation);
    animation->setAnimationPos(true_pos);

    auto true_range = new AttackRange(
        rangeType::Rectangle,
        getComp<CompType::POSITION>()->getSize()
    );
    true_range->setPosition(true_pos);

    addComp<CompType::HP>(data.HP);
    addComp<CompType::ATTACK>(data.damage, data.CD, true_range);
    getComp<CompType::ATTACK>()->setAttackFunc(zombieAttackPlant);
}

void Zombie::_statusFunction()
{
    auto status = getStatus();
    auto animationComp = getComp<CompType::ANIMATION>();
    if(animationComp) {
        animationComp->updateAnimationStatus(
            animationStatus[status]
        );
    }

    auto moveComp = getComp<CompType::MOVEMENT>();
    if(status == EntityStatus::Normal) {
        if(moveComp) {
            moveComp->setDir(Direction::DIR::RIGHT);
        }
    } else if(status == EntityStatus::Attack) {
        if(moveComp) {
            moveComp->setDir(Direction::DIR::STOP);
        }
    } else if(status == EntityStatus::Died) {
        if(moveComp) {
            moveComp->setDir(Direction::DIR::STOP);
        }
        kill();
    }
}
