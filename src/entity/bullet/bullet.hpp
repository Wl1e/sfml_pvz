#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>

#include <base/direction.hpp>
#include <entity/entity.hpp>

namespace demo {

struct BulletData
{
    // 这部分由plant提供
    int damage; // 伤害
    sf::Vector2i start; // 起始位置
    Direction dir; // 飞行方向
    int length; // 飞行距离

    // 这部分后续分离出去
    sf::Vector2u size; // 大小
    bool piercing; // 灵体
    int speed; // 飞行速度
    std::string animation; // 动画
};

class Bullet : public Entity
{
public:
    explicit Bullet(const BulletData& data);

    void afterAttack();
    bool isPiercing() const
    {
        return m_data.piercing;
    }

protected:
    void _statusFunction() override;

private:
    BulletData m_data;
};

} // namespace demo