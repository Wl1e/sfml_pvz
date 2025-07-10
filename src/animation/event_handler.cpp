#include <iostream>

#include <animation/event_handler.hpp>
#include <animation/gamescene.hpp>
#include <components/position_comp.hpp>
#include <entity/tool/tool.hpp>
#include <event_manager.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void EventHandler::OnKeyPressed(
    RenderWindow* window, const Event::KeyPressed& event
)
{
    if(event.scancode == Keyboard::Scancode::Escape) {
        window->close();
    } else if(true) {
        // ...
    }
}
void EventHandler::OnClosed(
    RenderWindow* window, const Event::Closed&
)
{
    window->close();
}

static Mouse::Button pressed_button;
static Vector2i pressed_pos(-1, -1);

void EventHandler::OnMouseButtonPressed(
    GameScene* scene, const Event::MouseButtonPressed& event
)
{
    cout << event.position.x << ' ' << event.position.y << '\n';
    pressed_button = event.button;
    pressed_pos = event.position;
}

void EventHandler::OnMouseButtonReleased(
    GameScene* scene, const Event::MouseButtonReleased& event
)
{
    if(event.button == pressed_button) {
        if((event.position - pressed_pos).lengthSquared() > 10) {
            return;
        }
        scene->click(event.position);
    }
}

void EventHandler::OnMounseMove(
    GameScene* scene, const Event::MouseMoved& event
)
{
    auto hand = scene->getHand();
    if(!hand) {
        return;
    }

    // 目前没有全局事件触发(触发所有entity的某个事件)
    trigger(
        hand,
        EventType::MouseMove,
        make_any<Vector2i>(event.position)
    );
}