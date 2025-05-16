#pragma once

#include <components/animation_comp.hpp>
#include <components/component.hpp>
// #include <components/attack_comp.hpp>
#include <components/hp_comp.hpp>
#include <components/movement_comp.hpp>
#include <components/position_comp.hpp>

namespace demo {

class Factory
{
public:
    template<CompType cType, typename... Args>
    std::unique_ptr<Component> create(Args... args)
    {
        return std::make_unique<typename type2cls<cType>::type>(
            args...
        );
    }

    static Factory* getFactory()
    {
        static Factory f;
        return &f;
    }
};
} // namespace demo