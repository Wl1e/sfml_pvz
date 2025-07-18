#pragma once

#include <base/range.hpp>
#include <entity/attack.hpp>
#include <entity/entity.hpp>

namespace demo {

struct PlantData
{
    std::string name;
    std::string type;
    float HP;
    int CD;
    float damage;
    // 像土豆雷、倭瓜等有两个攻击范围
    // 土豆雷在僵尸进入‘攻击范围1’时会攻击‘攻击范围2’内的僵尸
    // 倭瓜则是选择‘攻击范围1’内的某个僵尸，然后攻击该僵尸‘攻击范围2’内的所有僵尸
    // 已修改，新增碰撞系统，土豆雷通过碰撞触发
    AttackRange* range;
    std::string animation;
    int frame2animation;
    SizeType size;
    std::string bullet_type;
};

class Plant : public Entity
{
public:
    explicit Plant(const PlantData&, const sf::Vector2i&);
    virtual ~Plant() = default;

    const std::string& getBulletType() const
    {
        return m_bullet_type;
    }

protected:
    void _statusFunction() override;

    virtual void _initComp(const PlantData&, const sf::Vector2i&);
    virtual void _initEvents();

private:
    std::string m_bullet_type;
};

} // namespace demo