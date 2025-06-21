#include <base/tools.hpp>
#include <entity/entity.hpp>
#include <event_manager.hpp>
#include <system/collision_system.hpp>

using namespace std;
using namespace demo;

void CollisionSystem::addEntity(Entity* entity)
{
    auto position = entity->getComp<CompType::POSITION>();
    assert(position);
    BaseSystem::addEntity(entity);
    m_entitys[getPath(position->getBottomPos())].insert(entity);
}

void CollisionSystem::delEntity(Entity* entity)
{
    auto position = entity->getComp<CompType::POSITION>();
    assert(position);
    BaseSystem::delEntity(entity);
    m_entitys[getPath(position->getBottomPos())].erase(entity);
}

void CollisionSystem::update()
{
    // 遍历每行实体，如有碰撞，触发该两实体的对应事件
    // TODO: 给trigger加std::any参数
}