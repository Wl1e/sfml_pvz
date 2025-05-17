#include <components/animation_comp.hpp>
#include <components/movement_comp.hpp>
#include <components/position_comp.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

const Vector2i err_pos = {-1, -1};

void Entity::updade()
{
    // TODO: 后续将计算分离出去，只有animation才在主线程更新
    for(auto& it : m_component) {
        it.second->update(this);
    }
}

const sf::Vector2i& demo::getEntityPosition(Entity* entity)
{
    Component* posComp;
    if(posComp = entity->getComp(CompType::POSITION); !posComp) {
        throw "dont have position";
    }

    auto p = castToComp<type2cls<CompType::POSITION>::type>(posComp);
    return p->getPos();
}

bool demo::overlay(Entity* entity1, Entity* entity2)
{
    if(!entity1->hasComp(CompType::POSITION)
       || !entity2->hasComp(CompType::POSITION)) {
        return false;
    }

    // FIXME: type2cls<CompType::POSITION>::type 重复过多
    auto posComp1 = castToComp<type2cls<CompType::POSITION>::type>(
        entity1->getComp(CompType::POSITION)
    );
    auto posComp2 = castToComp<type2cls<CompType::POSITION>::type>(
        entity2->getComp(CompType::POSITION)
    );
    return type2cls<CompType::POSITION>::type::overlay(
        *posComp1, *posComp2
    );
}

bool demo::isPlant(Entity* entity)
{
    return entity->getType() == EntityType::PLANT;
}
bool demo::isZombie(Entity* entity)
{
    return entity->getType() == EntityType::ZOMBIE;
}
bool demo::isBullet(Entity* entity)
{
    return entity->getType() == EntityType::BULLET;
}