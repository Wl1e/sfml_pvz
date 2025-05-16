#pragma once

#include <entity/components/component.hpp>
#include <entity/components/animation_comp.hpp>
// #include <entity/components/attack_comp.hpp>
#include <entity/components/hp_comp.hpp>
#include <entity/components/movement_comp.hpp>
#include <entity/components/position_comp.hpp>

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