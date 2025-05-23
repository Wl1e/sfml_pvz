#include <entity/attack.hpp>
#include <entity/zombie/zombie.hpp>

using namespace std;
using namespace sf;
using namespace demo;

extern unordered_map<EntityStatus, string> animationStatus;

Zombie::Zombie(const ZombieData& data, int path) :
    Entity(EntityType::ZOMBIE)
{
    addComp<CompType::MOVEMENT>(data.dir, data.speed, 999);
    addComp<CompType::POSITION>(
        axis2pos({GRASS_COUNT, path}), data.size
    );
    addComp<CompType::ANIMATION>(data.animation);
    getComp<CompType::ANIMATION>()->setUpdateInterval(
        data.frame2animation
    );
    addComp<CompType::HP>(data.HP);
    addComp<CompType::ATTACK>(
        data.damage,
        data.CD,
        getComp<CompType::POSITION>()->getHitbox(),
        getComp<CompType::POSITION>()->getPos()
    );
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
