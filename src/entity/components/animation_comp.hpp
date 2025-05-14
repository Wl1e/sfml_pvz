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
class Entity;

using PosFunction = std::function<const sf::Vector2i&()>;
using anime_frame = sf::Texture;

// bool demo::read_frames(
//     const string& path,
//     unordered_map<string, vector<anime_frame>>& result
// );

bool demo::read_frames(
    std::string_view path,
    unordered_map<string, vector<anime_frame>>& result
);

class AnimationComp : public Component
{
public:
    AnimationComp(const std::string& resource_path);
    AnimationComp(std::string_view resource_path);

    void update();

    void setScene(GameScene* scene);
    void setSize(const sf::Vector2u& size)
    {
        auto scale = sf::Vector2f(size).componentWiseDiv(
            sf::Vector2f(m_sprite->getTexture().getSize())
        );
        m_sprite->setScale(scale);
    }
    void setPosFunc(PosFunction func);

    const sf::Vector2i& defaultPosFunction(GameScene* scene);

protected:
    void updateAnimation();
    void updateAnimationStatus(string_view status);
    void updatePos();

private:
    Entity* m_entity;
    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Vector2i m_animation_offset;
    // 考虑anime_frame* ？
    std::unordered_map<std::string, std::vector<anime_frame>>*
        m_frames;

    PosFunction m_pos_func;
};

} // namespace demo