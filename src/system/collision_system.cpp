#include <base/tools.hpp>
#include <defines.hpp>
#include <entity/entity.hpp>
#include <event_manager.hpp>
#include <system/collision_system.hpp>

using namespace std;
using namespace demo;

CollisionSystem::CollisionSystem() : m_entitys(GRASS_PATH)
{
}

void CollisionSystem::addEntity(Entity* entity)
{
    auto position = entity->getComp<CompType::POSITION>();
    assert(position);
    printf(
        "%p %f %f\n",
        position,
        position->getBottomPos().x,
        position->getBottomPos().y
    );
    BaseSystem::addEntity(entity);
    m_entitys[getPath(position->getBottomPos())].insert(entity);
    // printf("add entity %p\n", entity);
}

void CollisionSystem::delEntity(Entity* entity)
{
    auto position = entity->getComp<CompType::POSITION>();
    assert(position);
    BaseSystem::delEntity(entity);
    m_entitys[getPath(position->getBottomPos())].erase(entity);
    // printf("del entity %p\n", entity);
}

void CollisionSystem::update()
{
    // 遍历每行实体，如有碰撞，触发该两实体的对应事件
    // 重大问题：没有判断两对象类型，会导致两叠着走的敌人重复触发
    // 修复思路：最近学习了godot引擎，可以参考它来分层
    for(const auto& entitys : m_entitys) {
        for(auto entityIter = entitys.begin();
            entityIter != entitys.end();
            ++entityIter) {
            auto targetIter = entityIter;
            ++targetIter;
            while(targetIter != entitys.end()) {
                if(_collision(*entityIter, *targetIter)) {
                    // 会导致多个碰撞信号
                    trigger(
                        *entityIter,
                        EventType::Collide,
                        std::make_any<Entity*>(*targetIter)
                    );
                    trigger(
                        *targetIter,
                        EventType::Collide,
                        std::make_any<Entity*>(*entityIter)
                    );
                }
                ++targetIter;
            }
        }
    }
}

bool CollisionSystem::_collision(
    const Entity* const entity1, const Entity* const entity2
) const
{
    auto position1 = entity1->getComp<CompType::POSITION>();
    auto position2 = entity2->getComp<CompType::POSITION>();
    assert(position1 && position2);

    if(position1->isIgnoreCollision()
       || position2->isIgnoreCollision()) {
        return false;
    }

    return position1->intersection(*position2);
}