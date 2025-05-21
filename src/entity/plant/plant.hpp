#pragma once

#include <entity/entity.hpp>

namespace demo {

struct PlantData
{
    int HP;
    int CD;
    int damage;
    AttackRange range;
    std::string animation;
};

class Plant : public Entity
{
public:
    explicit Plant(const PlantData& data) : Entity(EntityType::PLANT)
    {
    }
};

} // namespace demo