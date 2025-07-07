#include <entity/plant/mine_plant.hpp>
#include <event_manager.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void MinePlant::_initComp(
    const PlantData& data, const sf::Vector2i& pos
)
{
    auto attack = getComp<CompType::ATTACK>();
    attack->setAttackFunc(minePlantAttackZombie);
    attack->setBanAttack(true);
}

void MinePlant::_initEvents()
{
    registerEvent(
        this,
        EventType::Collide,
        [](Entity* entity, const std::any&) {
            if(auto attack = entity->getComp<CompType::ATTACK>();
               attack) {
                attack->attackInRange(entity);
                entity->updateStatus(EntityStatus::Death);
            }
        }
    );
}