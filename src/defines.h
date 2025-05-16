#pragma once

namespace demo {

const int window_length = 800;
const int window_wide = 800;

const int grass_length = 50;
const int grass_wide = 50;

const int grass_start_x = 100;
const int grass_start_y = 100;

const int grass_path = 5;

enum class direction
{
    NOT = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,

};

} // namespace demo