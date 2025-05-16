#pragma once

#include <entity/entity.h>

namespace demo {

enum PlantStatus
{
    Normal = 0,
    Attack,
    Died
};

class Plant;
void plantDiedHander(GameScene* scene, Plant* plant);

class Plant : public Entity
{
public:
    Plant(int HP, int CD) :
        Entity(EntityType::Plant), m_status(PlantStatus::Normal),
        m_HP(HP), m_CD(CD)
    {
    }

    void downHP(int value)
    {
        if(m_HP < value) {
            m_HP = 0;
            m_status = PlantStatus::Died;
            whenDied();
        } else {
            m_HP -= value;
        }
    }

    void setPlantPos(const Vector2i& pos_axis)
    {
        m_pos_axis = pos_axis;
        setPos(axis2pos(pos_axis));
    }

    const Vector2i& getAxisPos() const
    {
        return m_pos_axis;
    }

    void updateStatus(PlantStatus status);

    bool isDied() const
    {
        return m_status == PlantStatus::Died;
    }

    void whenDied();

protected:
    PlantStatus m_status;

    int m_HP;
    int m_CD;
    sf::Vector2i m_pos_axis;
};

class AttackPlant : public Plant
{
public:
    AttackPlant(int HP, int CD, int damage, int attack_range) :
        Plant(HP, CD), m_damage(damage), m_attack_range(attack_range)
    {
    }
    void update() override;

protected:
    virtual bool validAttack() = 0;
    virtual void attack() = 0;

protected:
    int m_damage;
    int m_attack_range;
};

// FIXME: 层次有些深入了，后续考虑改为组件模式
class BulletAttackPlant : public AttackPlant
{
public:
    BulletAttackPlant(int HP, int CD, int damage, int attack_range) :
        AttackPlant(HP, CD, damage, attack_range)
    {
    }
    bool validAttack() override;
    void attack() override;
};
} // namespace demo