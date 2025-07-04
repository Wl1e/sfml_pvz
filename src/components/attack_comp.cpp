#include <animation/gamescene.hpp>
#include <base/attack_range.hpp>
#include <components/attack_comp.hpp>
#include <components/hp_comp.hpp>
#include <entity/entity.hpp>
#include <entity/frame.hpp>
#include <event_manager.hpp>

using namespace std;
using namespace sf;
using namespace demo;

static const int MIN_RANGE = -10;
static const int MAX_RANGE = 1000;

AttackComp::AttackComp(int damage, Frame cd, AttackRange* range) :
    m_damage(damage), m_range(range), m_ban_attack(false), m_cd(cd),
    m_attackFrame(FrameManager::getInstance().getFrame()),
    m_attack(nullptr)
{
    // if(m_range.x < MIN_RANGE) {
    //     m_range.x = MIN_RANGE;
    // }
    // if(m_range.y > MAX_RANGE) {
    //     m_range.y = MAX_RANGE;
    // }
}

// 有个性能点，每次update要检测一次敌人，确定攻击又要检测一次，这里可以优化成通过trigger传过去或者存在哪里
// 暂时修复

void AttackComp::update(Entity* entity)
{
    if(auto move = entity->getComp<CompType::MOVEMENT>(); move) {
        m_range->updatePos(move->getMoveValue());
    }
#ifdef DEMO_DEBUG
    m_range->display(entity->getScene());
#endif

    vector<Entity*> enemys;
    if(m_range) {
        enemys = m_range->getEnemyInRange(entity);
        if(enemys.empty()) {
            if(entity->getStatus() == EntityStatus::Attack) {
                entity->updateStatus(EntityStatus::Normal);
            }
            return;
        }
    }

    if(!_validAttack()) {
        return;
    }

    entity->updateStatus(EntityStatus::Attack);
    trigger(
        entity,
        EventType::Attack,
        // enemys为局部变量，有危险
        make_any<vector<Entity*>*>(&enemys)
    );

    // FIXME: 改了之后子弹无法正常命中了
    // _attack(entity, enemys);
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
// bool AttackComp::_inAttackRange(Entity* entity)
// {
//     if(!entity->hasComp(CompType::POSITION)) {
//         return false;
//     }
//     // FIXME: 换成centerPos
//     auto posComp = entity->getComp<CompType::POSITION>();

//     m_range->getShape();
//     return false;
// }

void AttackComp::_updateAttackRange(Entity* entity)
{
    if(auto movement = entity->getComp<CompType::MOVEMENT>();
       movement) {
        m_range->updatePos(movement->getMoveValue());
    }

#ifdef DEMO_DEBUG
    m_range->display(entity->getScene());
#endif
}

void AttackComp::attack(
    Entity* entity, const vector<Entity*>& targets
)
{
    _attack(entity, targets);
}

void AttackComp::attackInRange(Entity* entity)
{
    if(!m_range) {
        return;
    }
    auto enemys = m_range->getEnemyInRange(entity);
    _attack(entity, enemys);
}

bool AttackComp::hasEnemys(Entity* entity)
{
    if(!m_range) {
        return false;
    }
    auto enemys = m_range->getEnemyInRange(entity);
    return !enemys.empty();
}