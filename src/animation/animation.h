#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <draw/drawable.h>

namespace demo {

class GameScene;
using anime_frame = sf::Texture;

std::optional<
    std::unordered_map<std::string, std::vector<anime_frame>>>
read_frames(const std::string& path);

std::optional<
    std::unordered_map<std::string, std::vector<anime_frame>>>
read_frames(std::string_view path);

class BaseAnimation : public Drawable
{
public:
    explicit BaseAnimation(GameScene* window);
    ~BaseAnimation();
    virtual void update() = 0;
    virtual void reset() = 0;
};

class Animation : public BaseAnimation
{
public:
    Animation(
        GameScene* window, const std::vector<anime_frame>& source
    );
    Animation(GameScene* window, std::string_view source_path);
    ~Animation();
    void update() override;
    void reset() override;

    void setIdx(size_t idx)
    {
        if(m_idx != idx) {
            setDrawContent(m_data[idx]);
        }
        m_idx = idx;
    }

protected:
    size_t m_idx;
    std::vector<anime_frame> m_data;
};

class AutoAnimation : public Animation
{
public:
    AutoAnimation(
        GameScene* window, const std::vector<anime_frame>& source
    );
    void update() override;
    void setUpdateCond(std::function<bool(sf::Event*)> func)
    {
        m_update_func = std::move(func);
    }

private:
    std::function<bool(sf::Event*)> m_update_func;
};

class MultiAnimation : public BaseAnimation
{
public:
    MultiAnimation(
        GameScene* window,
        const std::unordered_map<
            std::string,
            std::vector<anime_frame>>& source
    );
    ~MultiAnimation();

    void update() override;
    void reset() override;

    void setAniamtionStatus(const std::string& status)
    {
        m_status = status;
    }

private:
    std::unordered_map<std::string, std::vector<anime_frame>> m_data;
    std::string m_status;
    size_t idx;

    std::function<void(sf::Event*)> m_control_func;
};

} // namespace demo