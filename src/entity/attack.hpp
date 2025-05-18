#pragma once

namespace demo {

class Entity;
class Plant;
class Zombie;
class Bullet;

// 子弹可能攻击除僵尸外的其他实体?植物和僵尸类似?
// 第二个参数就是防止这些问题
// 这里的参数是传给attackComp当攻击函数用的
// 第一个参数设置为AttackComp，方便回去到一些属性（伤害、范围等）
void BulletAttackFunc(AttackComp*, Entity*);
void PlantAttackFunc(AttackComp*, Entity*);
void ZombieAttackFunc(AttackComp*, Entity*);

void plantAttackZombie(Plant* plant, Zombie* zombie);
void zombieAttackPlant(Zombie* zombie, Plant* plant);
void bulletAttackPlant(Bullet* bullet, Plant* plant);
void bulletAttackZombie(Bullet* bullet, Zombie* zombie);

} // namespace demo