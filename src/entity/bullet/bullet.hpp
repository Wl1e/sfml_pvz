#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>

#include <base/direction.hpp>
#include <entity/entity.hpp>

namespace demo {

struct PlantSupport
{
    int damage; // 伤害
    PositionType start; // 起始位置
    Direction dir; // 飞行方向
    int length; // 飞行距离
};
struct BulletSupport
{
    SizeType size; // 大小
    bool piercing; // 灵体
    int speed; // 飞行速度
    std::string animation; // 动画
};

struct BulletData
{
    BulletData() = delete;
    BulletSupport bulletData;
    PlantSupport plantData;
};

class Bullet : public Entity
{
public:
    explicit Bullet(const BulletData& data);
    ~Bullet() = default;

    void afterAttack();
    bool isPiercing() const
    {
        return m_data.bulletData.piercing;
    }

protected:
    void _statusFunction() override;

private:
    BulletData m_data;
};

} // namespace demo