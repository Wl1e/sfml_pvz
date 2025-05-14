#pragma once

namespace demo {

enum class CompType
{
    POSITION = 0,
    ANIMATION
};

class Component
{
public:
    Component() = default;
    ~Component() = default;

    virtual void update() = 0;
};

} // namespace demo
