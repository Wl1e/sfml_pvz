#include <base/attack_range.hpp>
#include <entity/attack.hpp>
#include <entity/plant/plant.hpp>
#include <event_manager.hpp>
#include <UI/defines.hpp>

using namespace std;
using namespace sf;
using namespace demo;

extern unordered_map<EntityStatus, string> animationStatus;
// 后续或许不同植物有不同的偏移，可以改成类变量
static const PositionType PLANT_ATTACK_OFFSET{30, 0};

// plant、zombie和bullet在构建上其实有不少相同之处，或许可以在他们和entity之间再插一个层级
Plant::Plant(const PlantData& data, const Vector2i& pos) :
    Entity(EntityType::PLANT, data.name),
    m_bullet_type(data.bullet_type)
{
    _initComp(data, pos);
    _initEvent(data.type);
}

void Plant::_statusFunction()
{
    auto status = getStatus();
    if(auto animationComp = getComp<CompType::ANIMATION>();
       animationComp) {
        animationComp->updateAnimationStatus(
            animationStatus[status]
        );
    }

    if(status == EntityStatus::Death) {
        kill();
    }
}

// 不同植物有太多自定义的东西了
// 需要一些定义了
void Plant::_initComp(const PlantData& data, const Vector2i& pos)
{
    auto true_pos = axis2pos(pos2axis(PositionType(pos)));

    addComp<CompType::HP>(data.HP);
    addComp<CompType::ANIMATION>(data.animation);

    auto animation = getComp<CompType::ANIMATION>();
    animation->setUpdateInterval(data.frame2animation);

    auto trueSize = fitableSize(animation->getAnimationSize());
    true_pos -= PositionType(trueSize.componentWiseDiv({2, 1}));
    animation->setAnimationPos(true_pos);

    addComp<CompType::POSITION>(
        RangeType::Rectangle, true_pos, SizeType(trueSize)
    );

    auto true_range = new AttackRange(data.range);
    true_range->setPosition(
        getComp<CompType::POSITION>()->getCenterPos()
    );
    addComp<CompType::ATTACK>(data.damage, data.CD, true_range);
    getComp<CompType::ATTACK>()->setAttackFunc(
        data.type == "shooter" ? plantAttackZombie
                               : minePlantAttackZombie
    );
}

static unordered_map<string, unordered_map<EventType, EventCallback>>
    events = {
        {"shooter",
         {{EventType::FinishAnimation,
           [](Entity* entity, const std::any&) {
               if(entity->getStatus() != EntityStatus::Attack) {
                   return;
               }
               if(auto attack = entity->getComp<CompType::ATTACK>();
                  attack) {
                   attack->attackInRange(entity);
               }
           }}}},
        {
            "mine",
            {{EventType::Collide,
              [](Entity* entity, const std::any&) {
                  if(auto attack =
                         entity->getComp<CompType::ATTACK>();
                     attack) {
                      attack->attackInRange(entity);
                      entity->updateStatus(EntityStatus::Death);
                  }
              }}},
        }
};

void Plant::_initEvent(const string& type)
{

    // registerEvent(
    //     this,
    //     EventType::FinishAnimation,
    //     [](Entity* entity, const std::any&) {
    //         if(entity->getStatus() != EntityStatus::Attack) {
    //             return;
    //         }
    //         if(auto attack = entity->getComp<CompType::ATTACK>();
    //            attack) {
    //             attack->attackInRange(entity);
    //         }
    //     }
    // );
    if(events.find(type) == events.end()) {
        return;
    }

    for(auto& [eventType, cb] : events[type]) {
        registerEvent(this, eventType, cb);
    }
}