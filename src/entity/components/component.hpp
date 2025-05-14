#pragma once

#include <memory>

namespace demo {

class Entity;

// update 顺序
enum class CompType
{
    POSITION = 0,
    AXIS_POSITION,
    MOVEMENT,
    ANIMATION
};

struct Compless
{
    bool operator()(const CompType t1, const CompType t2) const
    {
        return static_cast<size_t>(t1) < static_cast<size_t>(t2);
    }
};

class Component
{
public:
    Component() = default;
    ~Component() = default;

    virtual void update() = 0;

    virtual void whenAdded(Entity*) = 0;
};

using CompPtr = std::unique_ptr<Component>;

// template<class T>
// void registerComponent(CompType type);

// template<CompType type, typename... Args>
// CompPtr createComponent(CompType type);

} // namespace demo
