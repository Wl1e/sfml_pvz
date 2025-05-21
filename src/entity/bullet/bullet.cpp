#include <entity/attack.hpp>
#include <entity/bullet/bullet.hpp>

using namespace std;
using namespace sf;
using namespace demo;

Bullet::Bullet(const BulletData& data) :
    Entity(EntityType::BULLET), m_data(data)
{
    addComp<CompType::POSITION>(
        m_data.plantData.start, m_data.bulletData.size
    );
    addComp<CompType::MOVEMENT>(
        m_data.plantData.dir, m_data.bulletData.speed
    );
    addComp<CompType::ANIMATION>(m_data.bulletData.animation);
    addComp<CompType::ATTACK>(
        m_data.plantData.damage,
        0,
        sf::RectangleShape(),
        getComp<CompType::POSITION>()->getPos()
    );
    getComp<CompType::ATTACK>()->setAttackFunc(bulletAttackZombie);
}

void Bullet::afterAttack()
{
    if(isPiercing()) {
        return;
    }
    if(hasComp(CompType::MOVEMENT)) {
        getComp<CompType::MOVEMENT>()->setDir(Direction::DIR::STOP);
    }
    if(hasComp(CompType::POSITION)) {
        getComp<CompType::POSITION>()->setIgnoreCollision(true);
    }
    if(hasComp(CompType::ANIMATION)) {
        auto animationComp = getComp<CompType::ANIMATION>();
        // animationComp->updateAnimationStatus("finish?");
    }
}

unordered_map<EntityStatus, string> animationStatus{
    {EntityStatus::Normal, "normal"},
    {EntityStatus::Destroying, "destroying"},
    {EntityStatus::Destroyed, "destroyed"}
};

void Bullet::_statusFunction()
{
    auto status = getStatus();

    if(hasComp(CompType::ANIMATION)) {
        getComp<CompType::ANIMATION>()->updateAnimationStatus(
            animationStatus[status]
        );
    }

    if(hasComp(CompType::MOVEMENT)) {
        if(status == EntityStatus::Destroying
           || status == EntityStatus::Destroyed) {
            getComp<CompType::MOVEMENT>()->setDir(
                Direction::DIR::STOP
            );
        }
    }
}
