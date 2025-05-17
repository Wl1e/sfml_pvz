#pragma once

namespace demo {

class Plant;
class Zombie;
class Bullet;

void plantAttackZombie(Plant* plant, Zombie* zombie);
void zombieAttackPlant(Zombie* zombie, Plant* plant);
void bulletAttackPlant(Bullet* bullet, Plant* plant);
void bulletAttackZombie(Bullet* bullet, Zombie* zombie);

} // namespace demo