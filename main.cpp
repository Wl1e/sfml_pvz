#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

using namespace std;
using namespace sf;
using namespace literals;

unordered_map<Keyboard::Key, function<void(Window*)>>
    keyboard_event_handler{
        {Keyboard::Key::Escape,
         [](Window* window) { window->close(); }},
    };

template<class T>
int call_handler(const T& event, Window* win)
{
    return -1;
}

template<>
int call_handler<Event::MouseMoved>(
    const Event::MouseMoved& event, Window* win
)
{
    // printf("[%d, %d]\n", event.position.x, event.position.y);
    return 0;
}

template<>
int call_handler<Event::KeyPressed>(
    const Event::KeyPressed& event, Window* win
)
{
    Keyboard::Key code = event.code;
    if(!keyboard_event_handler.count(code)) {
        return -1;
    }
    keyboard_event_handler[code](win);
    return 0;
}

int handle_window_event(Window* win, const Event& event)
{
    if(event.is<Event::KeyPressed>()) {
        return call_handler(*event.getIf<Event::KeyPressed>(), win);
    } else if(event.is<Event::MouseMoved>()) {
        return call_handler(*event.getIf<Event::MouseMoved>(), win);
    }
    return 0;
}

void update_window(Window* win, CircleShape& shape)
{
    auto [x, y] = shape.getPosition();
    if(x + shape.getRadius() >= win->getPosition().x) {
        x = -1;
    }
    shape.setPosition({x + 1, y});
}

int main()
{
    RenderWindow window(
        VideoMode({800, 600}), "my window", Style::Resize
    );
    VertexArray lines(PrimitiveType::LineStrip, 100);
    lines[0] = {{1, 1}, Color::Green};
    lines[1] = {{100, 100}, Color::Blue};
    lines[2] = {{200, 1}, Color::White};
    lines[3] = {{300, 100}, Color::Red};
    lines[4] = {{400, 1}, Color::Red};
    lines[5] = {{500, 100}, Color::Red};
    CircleShape cs(50, 4);
    cs.setPosition({0, 0});
    cs.setFillColor(Color::Green);

    while(window.isOpen()) {
        while(auto event = window.pollEvent()) {
            if(!event.has_value()) {
                continue;
            }
            handle_window_event(&window, event.value());
        }
        // update_window(&window, cs);
        window.clear();
        window.draw(lines);
        window.display();
    }
    return 0;
}