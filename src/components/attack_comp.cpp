#include <animation/gamescene.hpp>
#include <base/range.hpp>
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

EntityType getEnemyType(Entity* entity)
{
    if(isPlant(entity)) {
        return EntityType::ZOMBIE;
    } else if(isBullet(entity)) {
        return EntityType::ZOMBIE;
    } else if(isZombie(entity)) {
        return EntityType::PLANT;
    } else {
        return EntityType::NONE;
    }
}

AttackComp::AttackComp(int damage, Frame cd, AttackRange* range) :
    m_damage(damage), m_range(range), m_ban_attack(false), m_cd(cd),
    m_attackFrame(FrameManager::getInstance().getFrame()),
    m_attack(nullptr)
{
    setRangeTransplant(m_range.get(), Color::Red);
}

// 有个性能点，每次update要检测一次敌人，确定攻击又要检测一次，这里可以优化成通过trigger传过去或者存在哪里
// 暂时修复

// attackComp负责敌人检测、存储攻击回调和触发Attack信号，是否真正攻击由实体判断

void AttackComp::update(Entity* entity)
{
    if(auto move = entity->getComp<CompType::MOVEMENT>(); move) {
        m_range->move(move->getMoveValue());
    }
#ifdef DEMO_DEBUG
    entity->getScene()->draw(m_range.get());
#endif

    // 被动攻击、休眠植物
    // 减少遍历提升性能
    if(m_ban_attack) {
        return;
    }

    EntityType enemyType = getEnemyType(entity);
    if(enemyType == EntityType::NONE) {
        return;
    }
    vector<Entity*> enemys;
    if(m_range) {
        enemys =
            m_range->getEntityInRange(entity->getScene(), enemyType);
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

    // _attack(entity, enemys);
}

bool AttackComp::_validAttack()
{
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
        m_range->move(movement->getMoveValue());
    }

#ifdef DEMO_DEBUG
    entity->getScene()->draw(m_range.get());
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
    EntityType enemyType = getEnemyType(entity);
    if(enemyType == EntityType::NONE) {
        return;
    }
    auto enemys =
        m_range->getEntityInRange(entity->getScene(), enemyType);
    _attack(entity, enemys);
}

bool AttackComp::hasEnemys(Entity* entity)
{
    if(!m_range) {
        return false;
    }
    EntityType enemyType = getEnemyType(entity);
    if(enemyType == EntityType::NONE) {
        return false;
    }
    auto enemys =
        m_range->getEntityInRange(entity->getScene(), enemyType);
    return !enemys.empty();
}