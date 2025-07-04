#include <animation/gamescene.hpp>
#include <base/attack_range.hpp>
#include <entity/attack.hpp>
#include <entity/bullet/bullet.hpp>
#include <event_manager.hpp>
#include <UI/defines.hpp>

using namespace std;
using namespace sf;
using namespace demo;

extern unordered_map<EntityStatus, string> animationStatus;
static const PositionType BULLET_ATTACK_OFFSET{0, 0};

Bullet::Bullet(const BulletData& data) :
    Entity(EntityType::BULLET, data.bulletName),
    m_piercing(data.bulletData.piercing)
{
    _initComp(data);
    _initEvent();
}

void Bullet::_statusFunction()
{
    auto status = getStatus();

    if(status == EntityStatus::Destroyed) {
        if(auto move = getComp<CompType::MOVEMENT>(); move) {
            move->setDir(Direction::DIR::STOP);
        }
        kill();
    }
}

void Bullet::_initComp(const BulletData& data)
{
    addComp<CompType::ANIMATION>(data.bulletData.animation);
    addComp<CompType::MOVEMENT>(
        data.plantData.dir,
        data.bulletData.speed,
        data.plantData.length
    );

    auto animationSize =
        getComp<CompType::ANIMATION>()->getAnimationSize();
    if(animationSize.x >= UI_DEFINE::GRASS_LENGTH) {
        animationSize.x = UI_DEFINE::GRASS_LENGTH - 10;
    }
    if(animationSize.y >= UI_DEFINE::GRASS_WIDE) {
        animationSize.y = UI_DEFINE::GRASS_WIDE - 10;
    }

    addComp<CompType::POSITION>(
        data.plantData.start, SizeType(animationSize)
    );

    auto true_range = new AttackRange(
        RangeType::Circle, SizeType(animationSize.x / 2, 0)
    );
    true_range->setPosition(data.plantData.start);
    addComp<CompType::ATTACK>(data.plantData.damage, 0, true_range);
    getComp<CompType::ATTACK>()->setAttackFunc(bulletAttackZombie);
}

void Bullet::_initEvent()
{
    // registerEvent(
    //     this,
    //     EventType::Attack,
    //     // 这里可以传enemys进去
    //     [](Entity* entity, const std::any&) {
    //         if(auto attack = entity->getComp<CompType::ATTACK>();
    //            attack) {
    //             attack->attackInRange(entity);
    //         }
    //     }
    // );
    registerEvent(
        this,
        EventType::Collide,
        [](Entity* entity, const std::any&) {
            if(auto attack = entity->getComp<CompType::ATTACK>();
               attack) {
                attack->attackInRange(entity);
            }
            printf("buller kill\n");
            if(auto position = entity->getComp<CompType::POSITION>();
               position) {
                position->setIgnoreCollision(true);
            }
        }
    );
}