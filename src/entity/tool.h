#pragma once

#include <entity/entity.h>

namespace demo {

class Tool : public Entity
{
public:
    Tool() : Entity(EntityType::Tool)
    {
    }
    void update() override
    {
    }
};

} // namespace demo