#include <base/attack_range.hpp>
#include <entity/attack.hpp>
#include <entity/zombie/zombie.hpp>
#include <event_manager.hpp>
#include <UI/defines.hpp>

using namespace std;
using namespace sf;
using namespace demo;

extern unordered_map<EntityStatus, string> animationStatus;

Zombie::Zombie(const ZombieData& data, int path) :
    Entity(EntityType::ZOMBIE, data.name)
{
    _initComp(data, path);
    _initEvent();
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
            moveComp->setDir(Direction::DIR::LEFT);
        }
    } else if(status == EntityStatus::Attack) {
        if(moveComp) {
            moveComp->setDir(Direction::DIR::STOP);
        }
    } else if(status == EntityStatus::Death) {
        if(moveComp) {
            moveComp->setDir(Direction::DIR::STOP);
        }
        kill();
    }
}

void Zombie::_initComp(const ZombieData& data, int path)
{
    auto true_pos = axis2pos({UI_DEFINE::GRASS_COUNT - 1, path});

    addComp<CompType::MOVEMENT>(data.dir, data.speed, 10000);
    addComp<CompType::ANIMATION>(data.animation);
    addComp<CompType::HP>(data.HP);

    auto animation = getComp<CompType::ANIMATION>();
    auto animationSize = animation->getAnimationSize();

    if(animationSize.x >= UI_DEFINE::GRASS_LENGTH) {
        animationSize.x = UI_DEFINE::GRASS_LENGTH - 10;
    }
    if(animationSize.y >= UI_DEFINE::GRASS_WIDE) {
        animationSize.y = UI_DEFINE::GRASS_WIDE - 10;
    }
    true_pos -= PositionType(animationSize.componentWiseDiv({2, 1}));
    addComp<CompType::POSITION>(true_pos, SizeType(animationSize));

    animation->setUpdateInterval(data.frame2animation);
    animation->setAnimationPos(true_pos);

    auto true_range = new AttackRange(
        RangeType::Rectangle,
        getComp<CompType::POSITION>()->getSize()
    );
    true_range->setPosition(true_pos);

    addComp<CompType::ATTACK>(data.damage, data.CD, true_range);
    getComp<CompType::ATTACK>()->setAttackFunc(zombieAttackPlant);
}

void Zombie::_initEvent()
{
    registerEvent(
        this,
        EventType::FinishAnimation,
        [](Entity* entity, const std::any&) {
            if(entity->getStatus() != EntityStatus::Attack) {
                return;
            }
            if(auto attack = entity->getComp<CompType::ATTACK>();
               attack) {
                attack->attackInRange(entity);
            }
        }
    );
}