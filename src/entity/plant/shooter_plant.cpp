#include <entity/plant/shooter_plant.hpp>

using namespace std;
using namespace sf;
using namespace demo;

// 不单开类嫌复杂，单开似乎又没多少代码。。。
void ShooterPlant::_initComp(
    const PlantData& data, const sf::Vector2i& pos
)
{
    Plant::_initComp(data, pos);
    getComp<CompType::ATTACK>()->setAttackFunc(plantAttackZombie);
}