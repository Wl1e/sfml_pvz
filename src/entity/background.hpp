#pragma once

#include <entity/entity.hpp>

namespace demo {

class Background : public Entity
{
public:
    explicit Background(
        std::string_view resource_path,
        const sf::Vector2i& pos,
        const sf::Vector2u& size
    )
    {
        addComp<CompType::POSITION>(pos, size);
        addComp<CompType::ANIMATION>(resource_path);
    }

protected:
    void _statusFunction() override
    {
    }
};

} // namespace demo