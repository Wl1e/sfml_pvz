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
    explicit Plant(const PlantData& data, const sf::Vector2i& pos);
    ~Plant() = default;

    void init(const PlantData&, const Vector2i&);

    const std::string& getBulletType() const
    {
        return m_bullet_type;
    }

protected:
    void _statusFunction() override;

private:
    std::string m_bullet_type;
};

} // namespace demo