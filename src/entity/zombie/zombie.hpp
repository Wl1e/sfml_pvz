#pragma once

#include <entity/entity.hpp>

namespace demo {

class Zombie : public Entity
{
public:
    explicit Zombie() : Entity(EntityType::ZOMBIE)
    {
    }

protected:
    void _statusFunction()
    {
    }
};

} // namespace demo