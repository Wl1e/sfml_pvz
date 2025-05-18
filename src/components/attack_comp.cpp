#include <components/attack_comp.hpp>
#include <components/hp_comp.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

static const int MIN_RANGE = -10;
static const int MAX_RANGE = 1000;

AttackComp::AttackComp(int damage, const Vector2i& range, int cd) :
    m_damage(damage), m_range(range), m_cd(cd)
{
    // if(m_range.x < MIN_RANGE) {
    //     m_range.x = MIN_RANGE;
    // }
    // if(m_range.y > MAX_RANGE) {
    //     m_range.y = MAX_RANGE;
    // }
}

void AttackComp::update(Entity*)
{
}

void AttackComp::attack(Entity* entity)
{
    if(!entity->hasComp(CompType::HP)) {
        return;
    }
    auto HPComp = entity->getComp<CompType::HP>();
    HPComp->downHP(m_damage);
}

void AttackComp::attack(std::vector<Entity*>*)
{
}