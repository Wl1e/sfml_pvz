#pragma once

#include <map>

#include <SFML/System/Vector2.hpp>

#include <components/component.hpp>
#include <components/component_factory.hpp>
#include <entity/defines.hpp>

namespace demo {

class GameScene;

class Entity
{
public:
    explicit Entity(EntityType type, const std::string& name) :
        m_type(type), m_status(EntityStatus::Normal), m_name(name)
    {
    }
    virtual ~Entity();

    template<CompType cType, typename... Args>
    void addComp(Args&&... args)
    {
        m_component[cType] =
            ComponentFactory::getFactory()->create<cType>(args...);
        m_component[cType]->whenAdd(this);
    }
    void delComp(CompType cType)
    {
        m_component[cType]->whenDel(this);
        m_component[cType] = nullptr;
    }
    void setScene(GameScene* scene)
    {
        m_scene = scene;
    }
    void updateStatus(EntityStatus status)
    {
        m_status = status;
        _statusFunction();
    }
    void kill();

    template<CompType type>
    typename type2cls<type>::type* getComp() const
    {
        if(!hasComp(type)) {
            return nullptr;
        }
        return castToComp<typename type2cls<type>::type>(
            m_component.at(type).get()
        );
    }
    GameScene* getScene()
    {
        return m_scene;
    }
    EntityType getType() const
    {
        return m_type;
    }
    EntityStatus getStatus() const
    {
        return m_status;
    }
    const std::string& getName() const
    {
        return m_name;
    }
    bool hasComp(CompType type) const
    {
        return m_component.find(type) != m_component.end();
    }

    // TODO: 可以根据需要新增beforeUpdate和afterUpdate
    virtual void update();
    // void updateAnimation();

    virtual void click(const sf::Vector2i& pos)
    {
    }

protected:
    // 子类重写函数，更新status时调用
    virtual void _statusFunction() = 0;

private:
    GameScene* m_scene;
    std::map<CompType, CompPtr, Compless> m_component;

    EntityType m_type;
    EntityStatus m_status;
    std::string m_name;
};

bool isPlant(Entity*);
bool isZombie(Entity*);
bool isBullet(Entity*);

PositionType getEntityPosition(Entity*);

bool entityOverlay(Entity* entity1, Entity* entity2);

} // namespace demo