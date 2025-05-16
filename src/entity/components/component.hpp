#pragma once

#include <map>
#include <memory>

namespace demo {

class Entity;

// update 顺序
enum class CompType
{
    MOVEMENT = 0,
    POSITION,
    ANIMATION,
    ATTACK
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

    virtual void update(Entity*) = 0;
};

using CompPtr = std::unique_ptr<Component>;

class MovementComp;
class PositionComp;
class AnimationComp;

template<class T>
T* castTo(Component* comp)
{
    return dynamic_cast<T*>(comp);
}

template<CompType cType>
struct type2cls
{};

#define BIND(cType, class)  \
    template<>              \
    struct type2cls<cType>  \
    {                       \
        using type = class; \
    };

BIND(CompType::MOVEMENT, MovementComp)
BIND(CompType::POSITION, PositionComp)
BIND(CompType::ANIMATION, AnimationComp)

} // namespace demo
