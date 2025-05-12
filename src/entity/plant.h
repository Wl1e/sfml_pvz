#pragma once

#include <entity/entity.h>

namespace demo {

enum class PlantStatus
{
    Normal = 0,
    Attack,
    Died
};

class Plant : public Entity
{
public:
    Plant() :
        Entity(EntityType::Plant), m_status(PlantStatus::Normal)
    {
    }

    void downHP(int value)
    {
        if(m_HP < value) {
            m_HP = 0;
            m_status = PlantStatus::Died;
        } else {
            m_HP -= value;
        }
    }

    void updateStatus(PlantStatus status);

    bool isDied() const
    {
        return m_status == PlantStatus::Died;
    }

    void whenDied();

protected:
    int m_HP;
    int m_CD;
    sf::Vector2i m_pos_axis;

    PlantStatus m_status;
};

class AttackPlant : public Plant
{
public:
    void update() override;

protected:
    bool validAttack();
    void attack();

private:
    int m_damage;
};

} // namespace demo