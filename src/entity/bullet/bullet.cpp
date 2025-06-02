#include <animation/gamescene.hpp>
#include <base/attack_range.hpp>
#include <entity/attack.hpp>
#include <entity/bullet/bullet.hpp>

using namespace std;
using namespace sf;
using namespace demo;

extern unordered_map<EntityStatus, string> animationStatus;
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
    auto animationSize =
        getComp<CompType::ANIMATION>()->getAnimationSize();
    addComp<CompType::ATTACK>(
        m_data.plantData.damage,
        0,
        new AttackRange(
            rangeType::Circle, SizeType(animationSize.x / 2, 0)
        )
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

void Bullet::_statusFunction()
{
    auto status = getStatus();

    if(status == EntityStatus::Destroyed) {
        if(auto move = getComp<CompType::MOVEMENT>(); move) {
            move->setDir(Direction::DIR::STOP);
        }
        kill();
    }
}
