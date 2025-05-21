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
    BULLET,
    TOOL
};

enum class EntityStatus
{
    Normal,
    Attack,
    Destroying,
    Destroyed,

    Clicked,
};

class Entity
{
public:
    explicit Entity(EntityType type = EntityType::NONE) :
        m_type(type), m_status(EntityStatus::Normal)
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
    void updateStatus(EntityStatus status)
    {
        m_status = status;
        _statusFunction();
    }

    template<CompType type>
    typename type2cls<type>::type* getComp()
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
    bool hasComp(CompType type)
    {
        return m_component.count(type) != 0;
    }

    // TODO: 可以根据需要新增beforeUpdate和afterUpdate
    void updade();

    virtual void click() = 0;

protected:
    // 子类重写函数，更新status时调用
    virtual void _statusFunction() = 0;

private:
    GameScene* m_scene;
    std::map<CompType, CompPtr, Compless> m_component;

    EntityType m_type;
    EntityStatus m_status;
};

bool isPlant(Entity*);
bool isZombie(Entity*);
bool isBullet(Entity*);

PositionType getEntityPosition(Entity*);

bool entityOverlay(Entity* entity1, Entity* entity2);

} // namespace demo