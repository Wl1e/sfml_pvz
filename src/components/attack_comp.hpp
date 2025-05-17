#pragma once

#include <functional>

#include <SFML/System/Vector2.hpp>

#include <components/component.hpp>

namespace demo {

class Bullet;

using AttackFunction = std::function<void()>;

class AttackComp : public Component
{
public:
    explicit AttackComp(
        int damage, const sf::Vector2i& range, int cd
    );
    ~AttackComp() = default;

    void update(Entity*) override;

private:
    bool validAttack();

private:
    int m_damage;
    sf::Vector2i m_range; // 包括身后判定，比如倭瓜
    int m_cd;

    AttackFunction m_attack;
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