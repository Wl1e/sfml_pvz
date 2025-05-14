#pragma once

#include <entity/entity.h>

namespace demo {

class Tool;
void moveUpdate(Tool* tool);

class Tool : public Entity
{
public:
    Tool() : Entity(EntityType::Tool)
    {
    }
    void update() override
    {
        moveUpdate(this);
        updateAnimation();
    }
};

} // namespace demo