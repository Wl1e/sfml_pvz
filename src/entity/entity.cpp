#include <animation/gamescene.hpp>
#include <components/animation_comp.hpp>
#include <components/movement_comp.hpp>
#include <components/position_comp.hpp>
#include <entity/entity.hpp>
#include <event_manager.hpp>

using namespace std;
using namespace sf;
using namespace demo;

const Vector2i err_pos = {-1, -1};

unordered_map<EntityStatus, string> animationStatus{
    {EntityStatus::Normal, "normal"},
    {EntityStatus::Attack, "attack"},
    {EntityStatus::Death, "death"},
    {EntityStatus::Clicked, "clicked"}
};

Entity::~Entity()
{
    for(auto& comp : m_component) {
        comp.second->whenDel(this);
    }
}

void Entity::updade()
{
    // TODO: 后续将计算分离出去，只有animation才在主线程更新
    for(auto& it : m_component) {
        it.second->update(this);
    }
}

void Entity::kill()
{
    auto delThis = [](Entity* entity, const std::any& args = any()) {
        // death动画被其他状态更新了?
        if(args.has_value() && any_cast<string>(args) != "died") {
            printf("err entity isnt death\n");
            return;
        }
        entity->getScene()->addHander([entity](GameScene* scene) {
            clearEvents(entity);
            scene->delEntity(entity);
        });
    };
    if(auto animation = getComp<CompType::ANIMATION>(); animation) {
        if(animation->updateAnimationStatus("died")) {
            registerEvent(this, EventType::FinishAnimation, delThis);
            return;
        }
    }
    delThis(this);
}

PositionType demo::getEntityPosition(Entity* entity)
{
    if(!entity->hasComp(CompType::POSITION)) {
        throw "dont have position";
    }
    auto posComp = entity->getComp<CompType::POSITION>();
    return posComp->getBottomPos();
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