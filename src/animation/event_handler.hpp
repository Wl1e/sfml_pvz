#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace demo {

class GameScene;

class EventHandler
{
public:
    static void OnKeyPressed(
        sf::RenderWindow* window, const sf::Event::KeyPressed&
    );
    static void
    OnClosed(sf::RenderWindow* window, const sf::Event::Closed&);
    static void OnMouseButtonPressed(
        GameScene* scene, const sf::Event::MouseButtonPressed&
    );
    static void OnMouseButtonReleased(
        GameScene* scene, const sf::Event::MouseButtonReleased&
    );
};

} // namespace demo