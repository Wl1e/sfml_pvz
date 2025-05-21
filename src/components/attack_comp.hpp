#pragma once

#include <functional>
#include <variant>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <base/tools.hpp>
#include <components/component.hpp>

namespace demo {

class Bullet;
class AttackComp;

// void defaultAttackFunc(Entity*);

// 再加一个ConvexShape?
using AttackRange =
    std::variant<sf::CircleShape, sf::RectangleShape>;
using AttackFunction = std::function<void(Entity*)>;

// 目前AttackComp包含的东西有些多了，可以考虑分割
class AttackComp : public Component
{
public:
    // 还需要传攻击范围的位置，有点丑陋
    explicit AttackComp(
        int damage,
        Frame cd,
        const AttackRange& range,
        const PositionType& pos
    );
    ~AttackComp() = default;

    void update(Entity*) override;

    void setAttackFunc(AttackFunction func)
    {
        m_attack = std::move(func);
    }
    void setBanAttack(bool value)
    {
        m_ban_attack = value;
    }
    // 为了通用
    // attackComp可能属于plant、zombie、bullet,分别得获取不同类型的敌人
    // 或许可以把这片逻辑分出去?
    std::vector<Entity*>
    getEnemyInRange(const std::vector<Entity*>&);
    int getDamage() const
    {
        return m_damage;
    }

private:
    bool _inAttackRange(Entity*);
    bool _validAttack();
    void _attack(Entity*);

    void _updateAttackRange(const sf::Vector2f& move);

private:
    int m_damage;
    AttackRange m_range;
    bool m_ban_attack;

    Frame m_cd;
    Frame m_attackFrame;

    AttackFunction m_attack;
};

} // namespace demo