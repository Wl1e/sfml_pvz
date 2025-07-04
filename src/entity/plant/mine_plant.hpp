#pragma once

#include <entity/plant/plant.hpp>

namespace demo {

class MinePlant : public Plant
{
public:
    MinePlant(const PlantData& data, const sf::Vector2i& pos) :
        Plant(data, pos)
    {
    }
    ~MinePlant() = default;

protected:
    void _initComp(const PlantData&, const sf::Vector2i&);
};

} // namespace demo