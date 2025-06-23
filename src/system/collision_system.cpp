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
    // TODO: 给trigger加std::any参数
    for(const auto& entitys : m_entitys) {
        for(auto entityIter = entitys.begin();
            entityIter != entitys.end();
            ++entityIter) {
            auto targetIter = entityIter;
            ++targetIter;
            while(targetIter != entitys.end()) {
                if(_collision(*entityIter, *targetIter)) {
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
                    printf("collide\n");
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

    return position1->getHitbox()
        .getGlobalBounds()
        .findIntersection(position2->getHitbox().getGlobalBounds())
        .has_value();
}