#include <animation/gamescene.hpp>
#include <draw/drawable.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <unordered_set>

using namespace sf;
using namespace std;

namespace demo {

Texture err_texture(Vector2u{1, 1});

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
}

} // namespace demo