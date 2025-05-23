#include <entity/zombie/zombie.hpp>

using namespace std;
using namespace sf;
using namespace demo;

Zombie::Zombie(const ZombieData& data, int path) :
    Entity(EntityType::ZOMBIE)
{
    addComp<CompType::MOVEMENT>(data.dir, data.speed, 999);
    addComp<CompType::POSITION>(
        axis2pos({GRASS_COUNT, path}), SizeType{50, 50}
    );
    addComp<CompType::ANIMATION>(data.animation);
    addComp<CompType::HP>(data.HP);
}