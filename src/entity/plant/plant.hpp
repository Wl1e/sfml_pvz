#pragma once

#include <base/attack_range.hpp>
#include <entity/attack.hpp>
#include <entity/entity.hpp>

namespace demo {

struct PlantData
{
    float HP;
    int CD;
    float damage;
    AttackRange range;
    std::string animation;
    int frame2animation;
    SizeType size;
    std::string bullet_type;
};

class Plant : public Entity
{
public:
    explicit Plant(const PlantData&, const sf::Vector2i&);
    ~Plant() = default;

    const std::string& getBulletType() const
    {
        return m_bullet_type;
    }

protected:
    void _statusFunction() override;

private:
    void _initComp(const PlantData&, const sf::Vector2i&);
    void _initEvent();

private:
    std::string m_bullet_type;
};

} // namespace demo