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
// 目前这个函数只支持射手类植物(不包括多线射手)使用

// 2.
// 想了下，攻击函数里自己获取敌人，然后攻击，全有attackComp完成会更繁琐（不同实体获取的敌人类型、数量都不同）

// 几个函数重复度有些高
void plantAttackZombie(
    Entity* entity, const vector<Entity*>& targets
)
{
    printf("%s attack\n", entity->getName().data());
    if(targets.empty()) {
        return;
    }
    auto plant = dynamic_cast<Plant*>(entity);
    assert(plant->hasComp(CompType::ATTACK));
    assert(plant->hasComp(CompType::POSITION));
    auto attackComp = plant->getComp<CompType::ATTACK>();
    auto posCmp = plant->getComp<CompType::POSITION>();

    // 子弹创建可以考虑加到updateStatus的更新回调里去
    // FIXME: 做不到和动画同步，有些麻烦
    // 要依赖动画组件吗?
    // 已修改为动画组件事件触发攻击
    auto bullet = BulletFactory::getFactory()->create(
        plant->getBulletType(),
        {attackComp->getDamage(),
         posCmp->getPos() + PositionType(61, 5),
         Direction::DIR::RIGHT,
         1000}
    );
    if(!bullet) {
        printf("plantAttackZombie: create bullet error\n");
        return;
    }
    entity->getScene()->addBullet(bullet);
}

void zombieAttackPlant(
    Entity* entity, const vector<Entity*>& targets
)
{
    printf("%s attack\n", entity->getName().data());
    auto zombie = dynamic_cast<Zombie*>(entity);
    assert(zombie->hasComp(CompType::ATTACK));
    assert(zombie->hasComp(CompType::POSITION));
    auto attackComp = zombie->getComp<CompType::ATTACK>();

    Entity* enemy = nullptr;
    for(auto target : targets) {
        if(!target || target->getStatus() == EntityStatus::Death) {
            continue;
        }
        enemy = target;
        break;
    }
    if(!enemy) {
        return;
    }

    auto hp = enemy->getComp<CompType::HP>();
    if(!hp || hp->isDied()) {
        return;
    }

    zombie->updateStatus(EntityStatus::Attack);
    // entity和componet关联太低了，组件都不知道自己的实体是谁...
    // 不知道这算好还是算坏
    hp->receiveDamage(enemy, attackComp->getDamage());
}

void bulletAttackPlant(
    Entity* entity, const vector<Entity*>& targets
)
{
}
void bulletAttackZombie(
    Entity* entity, const vector<Entity*>& targets
)
{
    auto bullet = dynamic_cast<Bullet*>(entity);
    assert(bullet->hasComp(CompType::ATTACK));
    assert(bullet->hasComp(CompType::POSITION));
    auto attackComp = bullet->getComp<CompType::ATTACK>();

    for(auto enemy : targets) {
        if(auto hp = enemy->getComp<CompType::HP>(); hp) {
            hp->receiveDamage(enemy, attackComp->getDamage());
        }
    }
}

void minePlantAttackZombie(
    Entity* entity, const vector<Entity*>& targets
)
{
    if(targets.empty()) {
        return;
    }
    auto plant = dynamic_cast<Plant*>(entity);
    assert(plant->hasComp(CompType::ATTACK));
    assert(plant->hasComp(CompType::POSITION));
    auto attackComp = plant->getComp<CompType::ATTACK>();
    auto posCmp = plant->getComp<CompType::POSITION>();

    auto centerEnemy = targets.front();
    // auto trueEnemys =

    for(auto enemy : targets) {
        if(auto hp = enemy->getComp<CompType::HP>(); hp) {
            hp->receiveDamage(enemy, attackComp->getDamage());
        }
    }
}

} // namespace demo