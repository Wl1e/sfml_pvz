#include <SFML/Graphics/VertexArray.hpp>

#include <UI/defines.hpp>
#include <UI/ui_layout.hpp>

using namespace sf;
using namespace demo;

VertexArray UILayout::display()
{
    VertexArray lines(PrimitiveType::Lines);
    float start_x = UI_DEFINE::GRASS_START_X;
    float end_x =
        start_x + UI_DEFINE::GRASS_COUNT * UI_DEFINE::GRASS_LENGTH;
    float start_y = UI_DEFINE::GRASS_START_Y;
    float end_y =
        start_y + UI_DEFINE::GRASS_PATH * UI_DEFINE::GRASS_WIDE;
    for(size_t idx = 0; idx < UI_DEFINE::GRASS_PATH; ++idx) {
        lines.append(
            Vertex{
                {start_x, start_y + idx * UI_DEFINE::GRASS_WIDE},
                Color::Blue
            }
        );
        lines.append(
            Vertex{
                {end_x, start_y + idx * UI_DEFINE::GRASS_WIDE},
                Color::Blue
            }
        );
    }
    for(size_t idx = 0; idx < UI_DEFINE::GRASS_COUNT; ++idx) {
        lines.append(
            Vertex{
                {start_x + idx * UI_DEFINE::GRASS_LENGTH, start_y},
                Color::Blue
            }
        );
        lines.append(
            Vertex{
                {start_x + idx * UI_DEFINE::GRASS_LENGTH, end_y},
                Color::Blue
            }
        );
    }
    return lines;
}