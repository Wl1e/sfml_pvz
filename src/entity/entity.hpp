#pragma once

#include <map>

#include <SFML/System/Vector2.hpp>

#include <components/component.hpp>
#include <components/component_factory.hpp>

namespace demo {

class GameScene;

class Entity
{
public:
    Entity() = default;
    ~Entity() = default;

    template<CompType cType, typename... Args>
    void addComp(Args&&... args)
    {
        m_component[cType] =
            Factory::getFactory()->create<cType>(args...);
    }
    Component* getComp(CompType type)
    {
        if(!hasComp(type)) {
            return nullptr;
        }
        return m_component.at(type).get();
    }
    void setScene(GameScene* scene)
    {
        m_scene = scene;
    }

    GameScene* getScene()
    {
        return m_scene;
    }
    bool hasComp(CompType type)
    {
        return m_component.count(type) != 0;
    }

    void updade();

private:
    GameScene* m_scene;
    std::map<CompType, CompPtr, Compless> m_component;
};

} // namespace demo