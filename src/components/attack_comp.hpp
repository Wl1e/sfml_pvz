#pragma once

#include <functional>

#include <SFML/System/Vector2.hpp>

#include <components/component.hpp>

namespace demo {

class Bullet;
class AttackComp;

// void defaultAttackFunc(Entity*);
// using AttackFunction = std::function<void(Entity*)>;

class AttackComp : public Component
{
public:
    explicit AttackComp(
        int damage, const sf::Vector2i& range, int cd
    );
    ~AttackComp() = default;

    void update(Entity*) override
    {
    }
    void attack(Entity*);
    void attack(std::vector<Entity*>*);

    // void setAttackFunc(AttackFunction func)
    // {
    //     m_attack = std::move(func);
    // }
    // 为了通用
    // attackComp可能属于plant、zombie、bullet,分别得获取不同类型的敌人
    // 或许可以把这片逻辑分出去?
    template<class enemyType>
    std::vector<Entity*>
    getEnemyInRange(const std::vector<enemyType*>& entity)
    {
        std::vector<Entity*> res;
        return res;
    }

private:
    bool validAttack();

private:
    int m_damage;
    sf::Vector2i m_range; // 包括身后判定，比如倭瓜
    int m_cd;

    // AttackFunction m_attack;
};

/*
 * 目前分配
 * 植物：攻击力，攻击范围
 * 子弹：是否穿透，飞行速度
 */

template<class T>
Bullet* createBullet(
    int m_damage,
    const sf::Vector2i& start_pos,
    const sf::Vector2i& end_pos
);

} // namespace demo