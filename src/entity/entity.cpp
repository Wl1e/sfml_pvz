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

bool demo::isPlant(Entity* entity)
{
    return entity->getType() == EntityType::PLANT;
}
bool demo::isZombie(Entity* entity)
{
    return entity->getType() == EntityType::ZOMBIE;
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