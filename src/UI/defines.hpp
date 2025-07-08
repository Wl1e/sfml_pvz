#pragma once

#include <base/tools.hpp>
namespace demo {

class UI_DEFINE
{
public:
    static const unsigned int WINDOW_LENGTH;
    static const unsigned int WINDOW_WIDE;

    // 草地横向长度
    static const int GRASS_LENGTH;
    // 草地纵向长度
    static const int GRASS_WIDE;

    static const int GRASS_START_X;
    static const int GRASS_START_Y;

    static const int GRASS_PATH;
    static const int GRASS_COUNT;

    static const PositionType SHOP_POSITION;
};

SizeType fitableSize(sf::Vector2u);

} // namespace demo