#pragma once

#include <entity/entity.hpp>

namespace demo {

class Tool : public Entity
{
public:
    explicit Tool() : Entity(EntityType::TOOL)
    {
    }

protected:
    void _statusFunction()
    {
    }
};

} // namespace demo