#include <entity/plant/mine_plant.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void MinePlant::_initComp(
    const PlantData& data, const sf::Vector2i& pos
)
{
    Plant::_initComp(data, pos);
    auto attack = getComp<CompType::ATTACK>();
    attack->setAttackFunc(minePlantAttackZombie);
    attack->setBanAttack(true);
}