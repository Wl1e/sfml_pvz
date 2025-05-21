#include <animation/gamescene.hpp>
#include <components/attack_comp.hpp>
#include <entity/attack.hpp>
#include <entity/bullet/factory.hpp>
#include <entity/entity.hpp>
#include <entity/plant/plant.hpp>
#include <entity/zombie/zombie.hpp>

using namespace std;
using namespace sf;
using namespace demo;

namespace demo {

// 这里的plant必须有AttackComp
// 这些函数在写完Attack内的函数后似乎就没必要了?

// 2.
// 想了下，攻击函数里自己获取敌人，然后攻击，全有attackComp完成会更繁琐（不同实体获取的敌人类型、数量都不同）
void plantAttackZombie(Entity* entity)
{
    printf("attack\n");
    auto plant = dynamic_cast<Plant*>(entity);
    auto attackComp = plant->getComp<CompType::ATTACK>();
    auto posCmp = plant->getComp<CompType::POSITION>();
    // 只支持同一行的僵尸检测，三线和毁灭菇用不了
    auto& enemys =
        plant->getScene()->getZombiesByPath(getPath(posCmp->getPos())
        );
    if(enemys.empty()) {
        return;
    }
    // 性能消耗、性能消耗、性能消耗、性能消耗、性能消耗、性能消耗、性能消耗
    auto targets =
        attackComp->getEnemyInRange({enemys.begin(), enemys.end()});
    if(targets.empty()) {
        return;
    }
    // FIXME
    // update animation
    auto bullet = BulletFactory::getFactory()->create(
        "Pea",
        {attackComp->getDamage(),
         posCmp->getPos(),
         Direction::DIR::RIGHT,
         1000}
    );
    if(!bullet) {
        printf("plantAttackZombie: create bullet error\n");
        return;
    }
    entity->getScene()->addBullet(bullet);
}

void zombieAttackPlant(Entity* entity)
{
    auto zombie = dynamic_cast<Zombie*>(entity);
    auto attackComp = zombie->getComp<CompType::ATTACK>();
    auto enemys = zombie->getScene()->getPlantByAxis(
        pos2axis(zombie->getComp<CompType::POSITION>()->getPos())
    );
    if(!enemys) {
        return;
    }
    auto targets = attackComp->getEnemyInRange({enemys});
    if(targets.empty()) {
        return;
    }
    auto enemy = targets.front();
    if(!enemy->hasComp(CompType::HP)) {
        return;
    }
    // FIXME: update zombie status, not update animation
    if(zombie->hasComp(CompType::ANIMATION)) {
        zombie->getComp<CompType::ANIMATION>()
            ->updateAnimationStatus("attack");
    }
    enemy->getComp<CompType::HP>()->downHP(attackComp->getDamage());
}
void bulletAttackPlant(Bullet* bullet)
{
}
void bulletAttackZombie(Entity* entity)
{
    auto bullet = dynamic_cast<Bullet*>(entity);
    auto attackComp = bullet->getComp<CompType::ATTACK>();
    auto& enemys = bullet->getScene()->getZombiesByPath(
        getPath(bullet->getComp<CompType::POSITION>()->getPos())
    );
    if(enemys.empty()) {
        return;
    }

    // 子弹只有触碰才会造成伤害
    for(auto enemy : enemys) {
        if(!enemy->hasComp(CompType::HP)) {
            continue;
        }
        if(entityOverlay(bullet, enemy)) {
            enemy->getComp<CompType::HP>()->downHP(
                attackComp->getDamage()
            );
            if(!bullet->isPiercing()) {
                bullet->updateStatus(EntityStatus::Destroying);
            }
        }
    }
}

// void BulletAttackFunc(
//     AttackComp* attackComp, std::vector<Entity*>* victims
// )
// {
//     auto victim = victims->front();
//     if(!victim->hasComp(CompType::HP)) {
//         return;
//     }
//     auto HPComp = victim->getComp<CompType::HP>();
//     HPComp->downHP(attackComp->getDamage());
// }
// void PlantAttackFunc(
//     AttackComp* attackComp, std::vector<Entity*>* victims
// )
// {
//     // FIXME: Pea应该从Entity中得到
//     auto bullet = BulletFactory::getFactory()->create("Pea");
//     // 需要将bullet加到scene中
// }
// void ZombieAttackFunc(
//     AttackComp* attackComp, std::vector<Entity*>* victims
// )
// {
// }

} // namespace demo