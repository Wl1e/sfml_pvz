#pragma once

#include <map>

#include <SFML/System/Vector2.hpp>

#include <entity/components/animation_comp.hpp>
#include <entity/components/component.hpp>
#include <entity/components/position_comp.hpp>

namespace demo {

class GameScene;

class Entity
{
public:
    Entity() = default;
    ~Entity() = default;

    template<CompType type, typename... Args>
    constexpr void addComp(Args&&... args)
    {
        // fixme
        if constexpr(type == CompType::POSITION) {
            m_component[type] = std::make_unique<PositionComp>(
                std::forward<Args>(args)...
            );
        } else if constexpr(type == CompType::AXIS_POSITION) {
            m_component[type] = std::make_unique<AxisPositionComp>(
                std::forward<Args>(args)...
            );
        } else if constexpr(type == CompType::ANIMATION) {
            m_component[type] = std::make_unique<AnimationComp>(
                std::forward<Args>(args)...
            );
        }
        m_component[type]->whenAdded(this);
    }
    void setScene(GameScene* scene)
    {
        m_scene = scene;
    }
    GameScene* getScene()
    {
        return m_scene;
    }
    const sf::Vector2i& getPos();

    void updade();

private:
    GameScene* m_scene;
    std::map<CompType, CompPtr, Compless> m_component;
};

} // namespace demo