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
    _initEvent();
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

    if(status == EntityStatus::Died) {
        kill();
    }
}

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
        true_pos, SizeType(trueSize.componentWiseDiv({2, 1}))
    );

    auto true_range = new AttackRange(data.range);
    true_range->setPosition(
        getComp<CompType::POSITION>()->getCenterPos()
    );
    addComp<CompType::ATTACK>(data.damage, data.CD, true_range);
    getComp<CompType::ATTACK>()->setAttackFunc(plantAttackZombie);
}

void Plant::_initEvent()
{
    registerEvent(
        this,
        EventType::FinishAnimation,
        [](Entity* entity, const std::any&) {
            if(entity->getStatus() != EntityStatus::Attack) {
                return;
            }
            if(auto attack = entity->getComp<CompType::ATTACK>();
               attack) {
                attack->attack(entity);
            }
        }
    );
    // 由于comp的初始化没有entity，所以暂时放在这
    registerEvent(
        this,
        EventType::DownHP,
        [](Entity* entity, const std::any&) {
            if(auto animation =
                   entity->getComp<CompType::ANIMATION>();
               animation) {
                animation->setColor(Color(255, 255, 255, 100));
            }
        }
    );
}