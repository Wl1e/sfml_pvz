#include <animation/gamescene.hpp>
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

void Entity::kill()
{
    if(hasComp(CompType::MOVEMENT)) {
        getComp<CompType::MOVEMENT>()->setDir(Direction::DIR::STOP);
    }
    getScene()->addHander([this](GameScene* scene) {
        scene->delEntity(this);
    });
}

PositionType demo::getEntityPosition(Entity* entity)
{
    if(!entity->hasComp(CompType::POSITION)) {
        throw "dont have position";
    }
    auto posComp = entity->getComp<CompType::POSITION>();

    return posComp->getPos();
}

bool demo::entityOverlay(Entity* entity1, Entity* entity2)
{
    if(!entity1->hasComp(CompType::POSITION)
       || !entity2->hasComp(CompType::POSITION)) {
        return false;
    }

    // FIXME: type2cls<CompType::POSITION>::type 重复过多
    auto posComp1 = entity1->getComp<CompType::POSITION>();
    auto posComp2 = entity2->getComp<CompType::POSITION>();
    return posComp1->intersection(*posComp2);
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