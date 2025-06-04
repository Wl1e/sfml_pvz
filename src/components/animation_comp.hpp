#pragma once

#include <functional>
#include <string>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <base/tools.hpp>
#include <components/component.hpp>

namespace demo {

class GameScene;

using PosFunction = std::function<const sf::Vector2i&()>;
using SceneFunction = std::function<GameScene*()>;
using anime_frame = sf::Texture;

std::string read_frames(
    std::string_view path,
    std::unordered_map<std::string, std::vector<anime_frame>>& result
);

// FIXME: 后续可以分成animation和render，拆分功能

class AnimationComp : public Component
{
public:
    explicit AnimationComp(std::string_view resource_path) :
        m_frames(
            std::make_unique<std::unordered_map<
                std::string,
                std::vector<anime_frame>>>()
        ),
        m_idx(0), m_last_frame(0), m_interval(1)
    {
        m_status = read_frames(resource_path, *m_frames);
        m_sprite = std::make_unique<sf::Sprite>(
            m_frames->at(m_status)[m_idx]
        );
    }
    ~AnimationComp() = default;

    void update(Entity*) override;
    void updateAnimationStatus(std::string_view status);

    void setSize(const sf::Vector2f& size)
    {
        auto scale = size.componentWiseDiv(
            sf::Vector2f(m_sprite->getTexture().getSize())
        );
        m_sprite->setScale(scale);
    }
    void setUpdateInterval(int interval)
    {
        m_interval = interval;
    }
    void setAnimationPos(const PositionType& pos)
    {
        m_sprite->setPosition(pos);
    }

    sf::Vector2u getAnimationSize() const
    {
        return m_sprite->getTexture().getSize();
    }

protected:
    void _updateAnimation();
    void _updatePos(const PositionType&);

private:
    std::unique_ptr<sf::Sprite> m_sprite;

    // 考虑anime_frame* ？
    std::unique_ptr<
        std::unordered_map<std::string, std::vector<anime_frame>>>
        m_frames;
    std::string m_status;
    size_t m_idx;

    int m_last_frame;
    int m_interval;
};

} // namespace demo