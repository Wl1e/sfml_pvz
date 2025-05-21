#pragma once

#include <entity/entity.hpp>

namespace demo {

class Tool : public Entity
{
public:
    explicit Tool() : Entity(EntityType::TOOL)
    {
    }

    void click() override
    {
    }

protected:
    void _statusFunction()
    {
    }
};

} // namespace demo