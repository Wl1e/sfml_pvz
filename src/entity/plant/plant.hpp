#pragma once

#include <entity/attack.hpp>
#include <entity/entity.hpp>

namespace demo {

struct PlantData
{
    int HP;
    int CD;
    int damage;
    AttackRange range;
    std::string animation;
    SizeType size;
};

class Plant : public Entity
{
public:
    explicit Plant(const PlantData& data, const sf::Vector2i& pos) :
        Entity(EntityType::PLANT)
    {
        addComp<CompType::POSITION>(PositionType(pos), data.size);
        addComp<CompType::HP>(data.HP);
        addComp<CompType::ANIMATION>(data.animation);
        addComp<CompType::ATTACK>(
            data.damage,
            data.CD,
            data.range,
            getComp<CompType::POSITION>()->getPos()
        );
        getComp<CompType::ATTACK>()->setAttackFunc(
            plantAttackZombie
        );
        getComp<CompType::ATTACK>()->setBanAttack(true);
    }

    // 比如玉米加农炮
    void click() override
    {
        plantAttackZombie(this);
    }

protected:
    void _statusFunction() override
    {
    }
};

} // namespace demo