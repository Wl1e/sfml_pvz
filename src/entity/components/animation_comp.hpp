#pragma once

#include <functional>
#include <memory>
#include <string>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <entity/components/component.hpp>

namespace demo {

class GameScene;

using PosFunction = std::function<void()>;

class AnimationComp : public Component
{
public:
    AnimationComp(const std::string& resource_path);
    AnimationComp(std::string_view resource_path);

    void update();

    void setScene(GameScene* scene)
    {
        m_scene = scene;
    }
    void setSize(const sf::Vector2u& size)
    {
        auto scale = sf::Vector2f(size).componentWiseDiv(
            sf::Vector2f(m_sprite->getTexture().getSize())
        );
        m_sprite->setScale(scale);
    }

private:
    GameScene* m_scene;

    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Vector2i m_animation_offset;

    PosFunction m_pos_func;
};

} // namespace demo