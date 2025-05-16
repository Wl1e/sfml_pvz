#pragma once

#include <functional>
#include <string>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <components/component.hpp>

namespace demo {

class GameScene;

using PosFunction = std::function<const sf::Vector2i&()>;
using SceneFunction = std::function<GameScene*()>;
using anime_frame = sf::Texture;

// bool demo::read_frames(
//     const string& path,
//     unordered_map<string, vector<anime_frame>>& result
// );

bool read_frames(
    std::string_view path,
    std::unordered_map<std::string, std::vector<anime_frame>>& result
);

// FIXME: 后续可以分成animation和render，拆分功能

class AnimationComp : public Component
{
public:
    explicit AnimationComp(std::string_view resource_path) :
        m_animation_offset({-10, -10}),
        m_frames(
            std::make_unique<std::unordered_map<
                std::string,
                std::vector<anime_frame>>>()
        ),
        m_status("normal"), m_idx(0)
    {
        read_frames(resource_path, *m_frames);
        m_sprite = std::make_unique<sf::Sprite>(
            m_frames->at(m_status)[m_idx]
        );
    }
    ~AnimationComp() = default;

    void update(Entity*) override;
    void updateAnimationStatus(std::string_view status);

    void setSize(const sf::Vector2u& size)
    {
        auto scale = sf::Vector2f(size).componentWiseDiv(
            sf::Vector2f(m_sprite->getTexture().getSize())
        );
        m_sprite->setScale(scale);
    }

protected:
    void updateAnimation();
    void updatePos(Entity*);

private:
    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Vector2i m_animation_offset;

    // 考虑anime_frame* ？
    std::unique_ptr<
        std::unordered_map<std::string, std::vector<anime_frame>>>
        m_frames;
    std::string m_status;
    size_t m_idx;
};

} // namespace demo