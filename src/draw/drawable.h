#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

namespace demo {

class GameScene;

class Drawable
{
public:
    explicit Drawable(GameScene* scene);
    ~Drawable();

    void setDrawPosition(const sf::Vector2f& pos)
    {
        m_sprite.setPosition(pos);
    }
    void setScene(GameScene* scene)
    {
        m_master = scene;
    }

    sf::Vector2u getSize() const
    {
        return m_sprite.getTexture().getSize();
    }
    void setSize(const sf::Vector2u& size)
    {
        auto new_scale = size.componentWiseDiv(getSize());
        m_sprite.setScale(sf::Vector2f(new_scale));
    }

protected:
    void draw();
    void setDrawContent(const sf::Texture& content);

private:
    GameScene* m_master;
    sf::Sprite m_sprite;
};

} // namespace demo