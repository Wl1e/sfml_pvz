#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <animation/gamescene.h>
#include <draw/drawable.h>
#include <unordered_map>
#include <unordered_set>

using namespace sf;
using namespace std;

namespace demo {

Texture err_texture(Vector2u{0, 0});

Drawable::Drawable(GameScene* scene) :
    m_master(scene), m_sprite(err_texture)
{
}

void Drawable::draw()
{
    RenderWindow* scene = m_master->getNativeWindow();
    scene->draw(m_sprite);
}

Drawable::~Drawable()
{
}

void Drawable::setDrawContent(const sf::Texture& content)
{
    m_sprite.setTexture(content, true);
    auto [x_scale, y_scale] =
        sf::Vector2f(m_master->getSize())
            .componentWiseDiv(sf::Vector2f(content.getSize()));
    float scale = std::min(x_scale, y_scale);
    m_sprite.setScale({scale, scale});
}

} // namespace demo