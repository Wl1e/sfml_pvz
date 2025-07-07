#include <entity/plant/shooter_plant.hpp>
#include <event_manager.hpp>

using namespace std;
using namespace sf;
using namespace demo;

// 不单开类嫌复杂，单开似乎又没多少代码。。。
void ShooterPlant::_initComp(
    const PlantData& data, const sf::Vector2i& pos
)
{
    getComp<CompType::ATTACK>()->setAttackFunc(plantAttackZombie);
}

void ShooterPlant::_initEvents()
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