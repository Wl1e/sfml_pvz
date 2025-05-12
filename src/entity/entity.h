// #include <main/attack.hpp>
// #include <main/bullet.h>
// #include <main/entity.h>
// #include <main/game.h>
// #include <main/plant.h>
// #include <main/tools.h>
// #include <main/zombie.h>
#pragma once

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string_view>

#pragma once

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
    Entity(EntityType type) :
        m_scene(nullptr), m_type(type), m_pos({0, 0}),
        m_size({0, 0}), m_animation(nullptr)
    {
    }
    Entity(EntityType type, std::string_view source_path);
    ~Entity() = default;
    void setSize(const sf::Vector2u& size)
    {
        m_size = size;
    }
    void setPos(const sf::Vector2i& pos)
    {
        m_pos = pos;
    }
    void setScene(GameScene* scene);

    virtual void update() = 0;

protected:
    void updateAnimation();

protected:
    GameScene* m_scene;

    EntityType m_type;
    sf::Vector2i m_pos;
    sf::Vector2u m_size;

private:
    std::unique_ptr<Animation> m_animation;
};

} // namespace demo