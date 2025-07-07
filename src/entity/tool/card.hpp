#pragma once

#include <string_view>

#include <base/tools.hpp>

namespace demo {

class Background;
class PlantCreator;

class Card
{
public:
    Card(std::string_view, const PositionType&, const SizeType&);
    ~Card() = default;

private:
    std::unique_ptr<Background> m_background;
    std::unique_ptr<PlantCreator> m_plantCreator;
};

} // namespace demo