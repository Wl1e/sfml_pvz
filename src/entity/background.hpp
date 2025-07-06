#pragma once

#include <entity/entity.hpp>

namespace demo {

class Background : public Entity
{
public:
    explicit Background() : Entity(EntityType::NONE, "Background")
    {
    }
    void init(
        std::string_view resource_path,
        const PositionType& pos,
        const SizeType& size
    )
    {
        addComp<CompType::POSITION>(
            RangeType::Rectangle, pos, size, true
        );
        addComp<CompType::ANIMATION>(resource_path);
        getComp<CompType::ANIMATION>()->setSize(size);
    }
    ~Background() = default;

protected:
    void _statusFunction() override
    {
    }
};

} // namespace demo