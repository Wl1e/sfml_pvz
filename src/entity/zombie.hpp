#pragma once

#include <entity/entity.hpp>

namespace demo {

class Zombie : public Entity
{
public:
    Zombie() : Entity(EntityType::ZOMBIE)
    {
    }
};

} // namespace demo