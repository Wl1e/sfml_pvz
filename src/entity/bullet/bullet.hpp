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
    std::string bulletName;
    BulletSupport bulletData;
    PlantSupport plantData;
};

class Bullet : public Entity
{
public:
    explicit Bullet(const BulletData& data);
    ~Bullet() = default;

    bool isPiercing() const
    {
        return m_piercing;
    }

protected:
    void _statusFunction() override;

    void _initComp(const BulletData& data);
    void _initEvent();

private:
    bool m_piercing;
};

} // namespace demo