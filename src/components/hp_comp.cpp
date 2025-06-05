#include <components/hp_comp.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace demo;

void HPComp::update(Entity* entity)
{
    // TODO: 更新实体状态
    if(isDied()) {
        entity->updateStatus(EntityStatus::Died);
    }
}

void HPComp::downHP(float value)
{
    m_HP -= value;
    printf("down hp %f\n", value);
}