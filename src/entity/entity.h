#pragma once

#include <SFML/System/Vector2.hpp>
// #include <memory>
#include <string_view>

namespace demo {

class GameScene;
class Animation;

enum class EntityType
{
    None = 0,
    Plant,
    Zombie,
    Tool
};

class Entity
{
public:
    Entity(EntityType type);
    Entity(EntityType type, std::string_view source_path);
    ~Entity() = default;
    void setSize(const sf::Vector2u& size);
    void setPos(const sf::Vector2i& pos);
    void setScene(GameScene* scene);
    void setAniamtion(std::string_view source_path);

    EntityType getType() const
    {
        return m_type;
    }
    const sf::Vector2i& getPos() const
    {
        return m_pos;
    }
    const sf::Vector2u& getSize() const
    {
        return m_size;
    }

    virtual void update() = 0;

protected:
    void updateAnimation();

protected:
    GameScene* m_scene;

    EntityType m_type;
    sf::Vector2i m_pos;
    sf::Vector2u m_size;

private:
    // 考虑使用unique_ptr ?
    Animation* m_animation;
};

} // namespace demo