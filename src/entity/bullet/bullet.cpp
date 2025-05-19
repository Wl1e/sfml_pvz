#include <entity/bullet/bullet.hpp>

using namespace std;
using namespace sf;
using namespace demo;

Bullet::Bullet(const BulletData& data) :
    Entity(EntityType::BULLET), m_data(data)
{
    addComp<CompType::POSITION>(m_data.start, m_data.size);
    addComp<CompType::MOVEMENT>(m_data.dir, m_data.speed);
    addComp<CompType::ANIMATION>(m_data.animation);
    addComp<CompType::ATTACK>(m_data.damage, Vector2i(0, 0), 0);
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
    if(!hasComp(CompType::ANIMATION)) {
        return;
    }
    getComp<CompType::ANIMATION>()->updateAnimationStatus(
        animationStatus[getStatus()]
    );
}
