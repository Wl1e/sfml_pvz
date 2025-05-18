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

// plant必须有AttackComp
void plantAttackZombie(Plant* plant, Zombie* zombie)
{
    auto AttackComp = plant->getComp<CompType::ATTACK>();
    AttackComp->attack(zombie);
}
void plantAttackZombies(Plant* plant, vector<Zombie*>* zombies)
{
    auto AttackComp = plant->getComp<CompType::ATTACK>();
    vector<Entity*> targets = AttackComp->getEnemyInRange(*zombies);
    AttackComp->attack(&targets);
}
// 函数一模一样...
void zombieAttackPlant(Zombie* zombie, Plant* plant)
{
    auto AttackComp = zombie->getComp<CompType::ATTACK>();
    AttackComp->attack(plant);
}
void bulletAttackPlant()
{
}
void bulletAttackZombie(Bullet* bullet, Zombie* zombie)
{
    auto AttackComp = bullet->getComp<CompType::ATTACK>();
    AttackComp->attack(zombie);
    // bullet->afterAttack();
}

void BulletAttackFunc(AttackComp* attackComp, Entity* victim)
{
    if(!victim->hasComp(CompType::HP)) {
        return;
    }
    auto HPComp = victim->getComp<CompType::HP>();
    HPComp->downHP(attackComp->getDamage());
}
void PlantAttackFunc(AttackComp* attackComp, Entity* victim)
{
    auto bullet = BulletFactory::getFactory()->create("Pea");
}
void ZombieAttackFunc(AttackComp* attackComp, Entity* victim)
{
}

} // namespace demo