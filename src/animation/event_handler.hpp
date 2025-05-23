#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace demo {

class GameScene;

class EventHandler
{
public:
    static void
    OnKeyPressed(sf::RenderWindow*, const sf::Event::KeyPressed&);
    static void
    OnClosed(sf::RenderWindow*, const sf::Event::Closed&);
    static void OnMouseButtonPressed(
        GameScene*, const sf::Event::MouseButtonPressed&
    );
    static void OnMouseButtonReleased(
        GameScene*, const sf::Event::MouseButtonReleased&
    );
    static void
    OnMounseMove(GameScene*, const sf::Event::MouseMoved&);
};

} // namespace demo