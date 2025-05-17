#include <entity/bullet/bullet.hpp>

using namespace std;
using namespace sf;
using namespace demo;

Bullet::Bullet(const BulletData& data) :
    Entity(EntityType::BULLET), m_data(data)
{
    addComp<CompType::MOVEMENT>(m_data.dir, m_data.speed);
    addComp<CompType::POSITION>(m_data.start, m_data.size);
}