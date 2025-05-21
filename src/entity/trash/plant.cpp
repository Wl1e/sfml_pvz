#include <animation/gamescene.hpp>
#include <entity/bullet.h>
#include <entity/plant.h>
#include <game.h>

using namespace std;
using namespace sf;
using namespace demo;

static const string animation_state[]{"normal", "attack", "died"};

// FIXME: 有些冗余
void demo::plantDiedHander(GameScene* scene, Plant* plant)
{
    scene->addHander([&plant](GameScene* scene) {
        scene->delPlant(plant->getAxisPos());
    });
}

// ==================Plant==================

void Plant::updateStatus(PlantStatus status)
{
    if(m_status == status) {
        return;
    }

    m_status = status;
    setAniamtionStatus(animation_state[m_status]);
    updateAnimation();
}

void Plant::whenDied()
{
    plantDiedHander(m_scene, this);
}

// ==================AttackPlant==================

void AttackPlant::update()
{
    if(isDied()) {
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

// ==================BulletAttackPlant==================

bool BulletAttackPlant::validAttack()
{
    auto zombies = m_scene->getZombiesByPath(m_pos_axis.x);
    for(size_t idx = 0; idx < zombies.size(); ++idx) {
        if(!zombies[idx]) {
            continue;
        }
        int range = idx >= getPos().y;
        if(range >= 0 && range <= m_attack_range) {
            return true;
        }
    }
    return false;
}

void BulletAttackPlant::attack()
{
}