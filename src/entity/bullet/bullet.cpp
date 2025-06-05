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
    addComp<CompType::ANIMATION>(m_data.bulletData.animation);
    addComp<CompType::MOVEMENT>(
        m_data.plantData.dir,
        m_data.bulletData.speed,
        m_data.plantData.length
    );

    auto animationSize =
        getComp<CompType::ANIMATION>()->getAnimationSize();

    addComp<CompType::POSITION>(
        m_data.plantData.start, SizeType(animationSize)
    );

    auto true_range = new AttackRange(
        rangeType::Circle, SizeType(animationSize.x / 2, 0)
    );
    true_range->setPosition(m_data.plantData.start);
    addComp<CompType::ATTACK>(
        m_data.plantData.damage, 0, true_range
    );
    getComp<CompType::ATTACK>()->setAttackFunc(bulletAttackZombie);
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
