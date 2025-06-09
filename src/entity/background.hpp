#pragma once

#include <entity/entity.hpp>

namespace demo {

class Background : public Entity
{
public:
    explicit Background(
        std::string_view resource_path,
        const PositionType& pos,
        const SizeType& size
    )
    {
        addComp<CompType::POSITION>(pos, size);
        addComp<CompType::ANIMATION>(resource_path);
        getComp<CompType::ANIMATION>()->setSize(size);
    }
    ~Background() = default;

    void update();

protected:
    void _statusFunction() override
    {
    }
};

} // namespace demo