#include <components/attack_comp.hpp>
#include <components/hp_comp.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

static const int MIN_RANGE = -10;
static const int MAX_RANGE = 1000;

AttackComp::AttackComp(
    int damage, const AttackRange& range, int cd
) : m_damage(damage), m_range(range), m_cd(cd)
{
    // if(m_range.x < MIN_RANGE) {
    //     m_range.x = MIN_RANGE;
    // }
    // if(m_range.y > MAX_RANGE) {
    //     m_range.y = MAX_RANGE;
    // }
}

void AttackComp::update(Entity* entity)
{
    m_attack(entity);
}

// bool AttackComp::_validAttack(Entity* entity)
// {
//     return entity->getScene()->getEnemys(entity) != nullptr;
// }

// void AttackComp::attack(std::vector<Entity*>* enemys)
// {
//     // m_attack(enemys);
// }

// 被重复调用，计算可能导致性能下降，合并到下方函数可以提速，但是会导致但函数体量过大
bool AttackComp::_inAttackRange(Entity* entity)
{
    if(!entity->hasComp(CompType::POSITION)) {
        return false;
    }
    // FIXME: 换成centerPos
    auto& pos = entity->getComp<CompType::POSITION>()->getPos();

    if(auto range = get_if<CircleShape>(&m_range); range) {
        const float radius = range->getRadius();
        const Vector2f center =
            range->getPosition() + sf::Vector2f(radius, radius);
        auto vector = center - Vector2f(pos);
        return vector.lengthSquared() <= radius;

    } else if(auto range = get_if<RectangleShape>(&m_range); range) {
        // 不涉及range旋转
        return range->getGlobalBounds().contains(Vector2f(pos));
    }
    return false;
}

std::vector<Entity*>
AttackComp::getEnemyInRange(const vector<Entity*>& enemys)
{
    std::vector<Entity*> res;
    for(auto enemy : enemys) {
        if(_inAttackRange(enemy)) {
            res.push_back(enemy);
        }
    }
    return res;
}