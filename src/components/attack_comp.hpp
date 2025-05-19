#pragma once

#include <functional>
#include <variant>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <components/component.hpp>

namespace demo {

class Bullet;
class AttackComp;

// void defaultAttackFunc(Entity*);
using AttackRange =
    std::variant<sf::CircleShape, sf::RectangleShape>;
using AttackFunction = std::function<void(Entity*)>;

class AttackComp : public Component
{
public:
    explicit AttackComp(
        int damage, const AttackRange& range, int cd
    );
    ~AttackComp() = default;

    void update(Entity*) override;
    // void attack(Entity*);
    // void attack(std::vector<Entity*>*);

    void setAttackFunc(AttackFunction func)
    {
        m_attack = std::move(func);
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
    // bool _validAttack(Entity*);

private:
    int m_damage;
    // 局限性太大了，导致getEnemyInRange都不好写
    // 普通植物是一行
    // 三线是上中下
    // 毁灭菇、寒冰菇是一个圆
    // 估计还得封装一个类 ?? 直接用sf::shape或许可以?
    AttackRange m_range; // 包括身后判定，比如倭瓜
    int m_cd;

    AttackFunction m_attack;
};

} // namespace demo