#pragma once

#include <entity/entity.hpp>

namespace demo {

// class HandTool;

class Tool : public Entity
{
public:
    explicit Tool(const std::string& name) :
        Entity(EntityType::TOOL, name)
    {
    }

protected:
    void _statusFunction()
    {
    }
};

// class HandTool : public Tool
// {
// public:
//     virtual void use(const sf::Vector2i& pos) = 0;
//     HandTool* createHand(const sf::Vector2i& pos) override
//     {
//     }

// protected:
//     void _statusFunction()
//     {
//     }
// };

} // namespace demo