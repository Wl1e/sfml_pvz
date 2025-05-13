#include <SFML/Graphics.hpp>
#include <animation/animation.h>
#include <iostream>

using namespace std;
using namespace sf;
using namespace demo;

optional<unordered_map<size_t, vector<anime_frame>>>
test_read_frame(string_view path)
{
    return read_frames(path);
}

int main()
{
    auto ores = test_read_frame(
        "/home/wlle/code/demo/sfml2/src/animation/source"
    );
    if(!ores.has_value()) {
        return -1;
    }
    auto res = ores.value();
    AutoAnimation ani(res[1]);
    Texture t;
    Sprite sp(t);
    RenderWindow window(
        VideoMode({1920, 1080}), "My Window", State::Fullscreen
    );

    while(window.isOpen()) {
        optional<Event> event;
        while(event = window.pollEvent(), event.has_value()) {
            if(event.value().is<Event::KeyPressed>()) {
                window.close();
            }
        }
        sp.setTexture(ani.update(), true);
        auto [old_x, old_y] = sp.getTexture().getSize();
        float scale =
            min((float)window.getSize().x / old_x,
                (float)window.getSize().y / old_y);
        sp.setScale({scale, scale});
        window.clear();
        window.draw(sp);
        window.display();
        sleep(300ms);
    }
    return 0;
}