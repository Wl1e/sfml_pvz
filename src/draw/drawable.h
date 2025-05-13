#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

// tmp
#include <iostream>

namespace demo {

class GameScene;

class Drawable
{
public:
    explicit Drawable(GameScene* scene);
    ~Drawable();

    void setDrawPosition(const sf::Vector2i& pos)
    {
        m_sprite.setPosition(sf::Vector2f(pos));
    }
    void setScene(GameScene* scene)
    {
        m_master = scene;
    }
    void setDrawSize(const sf::Vector2u& size)
    {
        auto new_scale = sf::Vector2f(size).componentWiseDiv(
            sf::Vector2f(getSize())
        );
        std::cout << "oldSize: (" << getSize().x << ' '
                  << getSize().y << ")\n";
        std::cout << "new_scale: (" << new_scale.x << ' '
                  << new_scale.y << ")\n";
        m_sprite.setScale(new_scale);
    }
    sf::Vector2f getPos() const
    {
        return m_sprite.getPosition();
    }

    sf::Vector2u getSize() const
    {
        return m_sprite.getTexture().getSize();
    }

protected:
    void draw();
    void setDrawContent(const sf::Texture& content);

private:
    GameScene* m_master;
    sf::Sprite m_sprite;
};

} // namespace demo