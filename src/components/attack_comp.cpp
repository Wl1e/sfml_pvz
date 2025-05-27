#include <components/attack_comp.hpp>
#include <components/hp_comp.hpp>
#include <entity/entity.hpp>
#include <entity/frame.hpp>

#include <animation/gamescene.hpp>

using namespace std;
using namespace sf;
using namespace demo;

static const int MIN_RANGE = -10;
static const int MAX_RANGE = 1000;

AttackComp::AttackComp(
    int damage,
    Frame cd,
    const AttackRange& range,
    const PositionType& pos
) :
    m_damage(damage), m_range(range), m_ban_attack(false), m_cd(cd),
    m_attackFrame(0)
{
    auto aRange = get_if<RectangleShape>(&m_range);
    if(aRange) {
        aRange->setPosition(pos);
    }
#ifdef DEMO_DEBUG
    if(aRange) {
        aRange->setFillColor(sf::Color::Transparent);
        aRange->setOutlineColor(sf::Color::Red);
        aRange->setOutlineThickness(1);
    }
#endif
    // if(m_range.x < MIN_RANGE) {
    //     m_range.x = MIN_RANGE;
    // }
    // if(m_range.y > MAX_RANGE) {
    //     m_range.y = MAX_RANGE;
    // }
}

void AttackComp::update(Entity* entity)
{
#ifdef DEMO_DEBUG
    if(auto range = get_if<RectangleShape>(&m_range)) {
        entity->getScene()->draw(*range);
    }
#endif
    // 和position分开更新有些奇怪，应该依赖position组件的
    if(entity->hasComp(CompType::MOVEMENT)) {
        _updateAttackRange(
            entity->getComp<CompType::MOVEMENT>()->getMoveValue()
        );
    }
    if(!_validAttack()) {
        return;
    }

    auto enemys = getEnemyInRange(entity);
    if(enemys.empty()) {
        if(entity->getStatus() == EntityStatus::Attack) {
            entity->updateStatus(EntityStatus::Normal);
        }
        return;
    }
    entity->updateStatus(EntityStatus::Attack);

    _attack(entity, enemys);
}

bool AttackComp::_validAttack()
{
    if(m_ban_attack) {
        return false;
    }
    if(!_checkCD()) {
        return false;
    }
    return true;
}

bool AttackComp::_checkCD()
{
    // cd检查；也可以换成定时器的模式，cd时长的定时器，到点重置
    Frame nowFrame = FrameManager::getInstance().getFrame();
    if(nowFrame - m_attackFrame >= m_cd) {
        m_attackFrame = nowFrame;
        return true;
    }
    return false;
}

void AttackComp::_attack(
    Entity* entity, const std::vector<Entity*>& enemys
)
{
    if(!m_attack) {
        return;
    }
    m_attack(entity, enemys);
}

// 被重复调用，计算可能导致性能下降，合并到下方函数可以提速，但是会导致但函数体量过大
bool AttackComp::_inAttackRange(Entity* entity)
{
    if(!entity->hasComp(CompType::POSITION)) {
        return false;
    }
    // FIXME: 换成centerPos
    auto posComp = entity->getComp<CompType::POSITION>();

    if(auto range = get_if<CircleShape>(&m_range); range) {
        return range->getGlobalBounds()
            .findIntersection(posComp->getHitbox().getGlobalBounds())
            .has_value();

    } else if(auto range = get_if<RectangleShape>(&m_range); range) {
        // 不涉及range旋转
        // 有些粗糙了
        return range->getGlobalBounds()
            .findIntersection(posComp->getHitbox().getGlobalBounds())
            .has_value();
    }
    return false;
}

std::vector<Entity*> AttackComp::getEnemyInRange(Entity* target)
{
    std::vector<Entity*> res;

    // auto enemys = target->getScene()->getEnemys(target);
    // for(auto enemy : enemys) {
    //     if(_inAttackRange(enemy)) {
    //         res.push_back(enemy);
    //     }
    // }
    return res;
}

void AttackComp::_updateAttackRange(const Vector2f& move)
{
    if(auto range = get_if<RectangleShape>(&m_range); range) {
        range->move(move);
    }
}