#include <animation/event_handler.hpp>
#include <animation/gamescene.hpp>
#include <components/position_comp.hpp>
#include <entity/tool/tool.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void EventHandler::OnKeyPressed(
    sf::RenderWindow* window, const sf::Event::KeyPressed& event
)
{
    if(event.scancode == sf::Keyboard::Scancode::Escape) {
        window->close();
    } else if(true) {
        // ...
    }
}
void EventHandler::OnClosed(
    sf::RenderWindow* window, const sf::Event::Closed&
)
{
    window->close();
}

static Mouse::Button pressed_button;
static sf::Vector2i pressed_pos(-1, -1);

void EventHandler::OnMouseButtonPressed(
    GameScene* scene, const sf::Event::MouseButtonPressed& event
)
{
    pressed_button = event.button;
    pressed_pos = event.position;
    // scene->click(pos);
}

void EventHandler::OnMouseButtonReleased(
    GameScene* scene, const sf::Event::MouseButtonReleased& event
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
    GameScene* scene, const sf::Event::MouseMoved& event
)
{
    auto hand = scene->getHand();
    if(!hand) {
        return;
    }

    if(!hand->hasComp(CompType::POSITION)) {
        return;
    }
    hand->getComp<CompType::POSITION>()->setPosition(
        PositionType(event.position)
    );
}