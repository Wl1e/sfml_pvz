#include <components/hp_comp.hpp>
#include <entity/entity.hpp>
#include <event_manager.hpp>

using namespace std;
using namespace demo;

void HPComp::update(Entity* entity)
{
    // TODO: 更新实体状态
    if(isDied()) {
        entity->updateStatus(EntityStatus::Died);
    }
}

void HPComp::_downHP(float value)
{
    m_HP -= value;
    printf("down hp %f\n", value);
}

// 为了事件特地加的函数，或许还有其他作用
void HPComp::receiveDamage(Entity* entity, float value)
{
    _downHP(value);
    trigger(entity, EventType::DownHP);
}