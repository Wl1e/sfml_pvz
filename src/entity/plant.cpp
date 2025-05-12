#include <entity/game.h>
#include <entity/plant.h>

using namespace std;
using namespace sf;
using namespace demo;

void Plant::updateStatus(PlantStatus status)
{
    if(m_status == status) {
        return;
    }

    m_status = status;
    updateAnimation();
}

void Plant::whenDied()
{
    m_scene->delEntity(this);
}

void AttackPlant::update()
{
    if(isDied()) {
        whenDied();
        return;
    }

    auto& zombies = m_scene->getZombiesByPath(m_pos_axis.x);
    if(zombies.empty()) {
        updateStatus(PlantStatus::Normal);
    } else {
        updateStatus(PlantStatus::Attack);
        attack();
    }
}
