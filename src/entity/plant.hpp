#pragma once

#include <entity/entity.hpp>

namespace demo {

struct PlantData
{
    int HP;
    int CD;
    int damage;
    int range;
};

class Plant : public Entity
{
public:
    Plant() : Entity(EntityType::PLANT)
    {
    }
};

Plant* createPlant(const PlantData& data);

} // namespace demo