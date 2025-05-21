#include <animation/gamescene.hpp>
#include <entity/attack.hpp>
#include <entity/bullet/bullet.hpp>

using namespace std;
using namespace sf;
using namespace demo;

static const PositionType BULLET_ATTACK_OFFSET{0, 0};

Bullet::Bullet(const BulletData& data) :
    Entity(EntityType::BULLET), m_data(data)
{
    addComp<CompType::POSITION>(
        m_data.plantData.start, m_data.bulletData.size
    );
    addComp<CompType::MOVEMENT>(
        m_data.plantData.dir,
        m_data.bulletData.speed,
        m_data.plantData.length
    );
    addComp<CompType::ANIMATION>(m_data.bulletData.animation);
    addComp<CompType::ATTACK>(
        m_data.plantData.damage,
        0,
        sf::RectangleShape(m_data.bulletData.size),
        getComp<CompType::POSITION>()->getPos()
            + BULLET_ATTACK_OFFSET
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

    if(status == EntityStatus::Destroyed) {
        if(hasComp(CompType::MOVEMENT)) {
            getComp<CompType::MOVEMENT>()->setDir(
                Direction::DIR::STOP
            );
        }
        getScene()->addHander([this](GameScene* scene) {
            scene->delBullet(this);
        });
    }
}
