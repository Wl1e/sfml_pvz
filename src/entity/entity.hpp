#pragma once

#include <map>

#include <SFML/System/Vector2.hpp>

#include <components/component.hpp>
#include <components/component_factory.hpp>

namespace demo {

class GameScene;

enum class EntityType
{
    NONE = 0,
    PLANT,
    ZOMBIE,
    TOOL
};

class Entity
{
public:
    Entity(EntityType type = EntityType::NONE) : m_type(type)
    {
    }
    ~Entity() = default;

    template<CompType cType, typename... Args>
    void addComp(Args&&... args)
    {
        m_component[cType] =
            Factory::getFactory()->create<cType>(args...);
    }
    void setScene(GameScene* scene)
    {
        m_scene = scene;
    }

    Component* getComp(CompType type)
    {
        if(!hasComp(type)) {
            return nullptr;
        }
        return m_component.at(type).get();
    }
    GameScene* getScene()
    {
        return m_scene;
    }
    EntityType getType() const
    {
        return m_type;
    }
    bool hasComp(CompType type)
    {
        return m_component.count(type) != 0;
    }

    // TODO: 可以根据需要新增beforeUpdate和afterUpdate
    void updade();

private:
    GameScene* m_scene;
    std::map<CompType, CompPtr, Compless> m_component;

    EntityType m_type;
};

bool isPlant(Entity*);
bool isZombie(Entity*);

const sf::Vector2i& getEntityPosition(Entity*);

} // namespace demo