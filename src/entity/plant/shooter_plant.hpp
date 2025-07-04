#pragma once

#include <entity/plant/plant.hpp>

namespace demo {

class ShooterPlant : public Plant
{
public:
    ShooterPlant(const PlantData& data, const sf::Vector2i& pos) :
        Plant(data, pos)
    {
    }
    ~ShooterPlant() = default;

protected:
    void _initComp(const PlantData&, const sf::Vector2i&);
};

} // namespace demo