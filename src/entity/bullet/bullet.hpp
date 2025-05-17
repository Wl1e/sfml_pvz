#pragma once

#include <SFML/System/Vector2.hpp>

#include <base/direction.hpp>
#include <entity/entity.hpp>

namespace demo {

struct BulletData
{
    int damage; // 伤害
    sf::Vector2i start; // 起始位置
    sf::Vector2u size; // 大小
    bool Piercing; // 灵体
    Direction dir; // 飞行方向
    int length; // 飞行距离
    int speed; // 飞行速度
};

class Bullet : public Entity
{
public:
    explicit Bullet(const BulletData& data);

private:
    BulletData m_data;
};

Bullet* CreateBullet(const BulletData& data)
{
    Bullet* bullet = new Bullet(data);
    return bullet;
}

} // namespace demo