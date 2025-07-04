#include <cmath>

#include <animation/gamescene.hpp>
#include <base/attack_range.hpp>
#include <entity/bullet/bullet.hpp>
#include <entity/entity.hpp>
#include <entity/plant/plant.hpp>
#include <entity/zombie/zombie.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void PlantGetEnemys(
    const AttackRange* range, GameScene* scene, vector<Entity*>& res
)
{
    RangeType rangeType = range->getRangeType();
    auto attackRange = range->getShape();
    if(!attackRange) {
        return;
    }
    // 杨桃、三线?
    if(rangeType == RangeType::Rectangle) {
        float degree = attackRange->getRotation().asDegrees();
        float int_degree;
        float value = modf(degree, &int_degree);

        unordered_set<Zombie*> enemys;
        // 纯直线（优化）
        if(value == 0.f && static_cast<int>(int_degree) % 180 == 0) {
            enemys = scene->getZombiesByPath(
                getPath(attackRange->getPosition())
            );
            for(auto enemy : enemys) {
                if(range->inRange(enemy)) {
                    res.push_back(enemy);
                }
            }
            return;
        }
    }
    // 另类攻击范围
    auto all_zombies = scene->getAllzombies();
    for(auto entitys : all_zombies) {
        for(auto enemy : entitys) {
            if(range->inRange(enemy)) {
                res.push_back(enemy);
            }
        }
    }
}

// 目前子弹圆形碰撞
void bulletGetEnemys(
    const AttackRange* range, GameScene* scene, vector<Entity*>& res
)
{
    auto enemys = scene->getZombiesByPath(
        getPath(range->getShape()->getPosition())
    );
    for(auto enemy : enemys) {
        if(range->inRange(enemy)) {
            res.push_back(enemy);
        }
    }
}

// 目前僵尸方形碰撞
void zombieGetEnemys(
    const AttackRange* range, GameScene* scene, vector<Entity*>& res
)
{
    auto enemys =
        scene->getPlantByAxis(pos2axis(range->getCenterPos()));
    if(!enemys) {
        return;
    }
    if(range->inRange(enemys)) {
        res.push_back(enemys);
    }
}

std::vector<Entity*> AttackRange::getEnemyInRange(Entity* entity)
{
    std::vector<Entity*> res;

    auto scene = entity->getScene();
    if(isZombie(entity)) {
        // TODO: 一个格子可能有多个植物
        zombieGetEnemys(this, scene, res);
    } else if(isBullet(entity)) {
        bulletGetEnemys(this, scene, res);
    } else if(isPlant(entity)) {
        PlantGetEnemys(this, scene, res);
    }
    return res;
}

bool AttackRange::_inRange(Entity* entity) const
{
    assert(entity->hasComp(CompType::POSITION));
    auto pos = entity->getComp<CompType::POSITION>();
    // 无法真正适配圆形
    return m_range->getGlobalBounds()
        .findIntersection(pos->getHitbox().getGlobalBounds())
        .has_value();
}

void AttackRange::display(GameScene* scene)
{
    scene->draw(*m_range);
}

AttackRange::AttackRange(RangeType type, const SizeType& size) :
    m_type(type), m_range(nullptr)
{
    if(m_type == RangeType::Rectangle) {
        m_range = new sf::RectangleShape(size);
    } else if(m_type == RangeType::Circle) {
        m_range = new sf::CircleShape(size.x);
    } else {
        // err
    }

#ifdef DEMO_DEBUG
    if(m_range) {
        m_range->setFillColor(sf::Color::Transparent);
        m_range->setOutlineColor(sf::Color::Red);
        m_range->setOutlineThickness(1);
    }
#endif
}

AttackRange::AttackRange(const AttackRange& range) :
    m_type(range.m_type)
{
    if(m_type == RangeType::Rectangle) {
        m_range = new sf::RectangleShape(
            *static_cast<sf::RectangleShape*>(range.m_range)
        );
    } else if(m_type == RangeType::Circle) {
        m_range = new sf::CircleShape(
            *static_cast<sf::CircleShape*>(range.m_range)
        );
    } else {
        // err
    }

#ifdef DEMO_DEBUG
    if(m_range) {
        m_range->setFillColor(sf::Color::Transparent);
        m_range->setOutlineColor(sf::Color::Red);
        m_range->setOutlineThickness(1);
    }
#endif
}

PositionType AttackRange::getCenterPos() const
{
    return m_range->getPosition() + m_range->getGeometricCenter();
}

void AttackRange::setPosition(const PositionType& pos)
{
    if(m_type == RangeType::Rectangle) {
        m_range->setPosition(pos);
    } else if(m_type == RangeType::Circle) {
        auto trueRange = dynamic_cast<sf::CircleShape*>(m_range);
        m_range->setPosition(
            pos
            - PositionType(
                trueRange->getRadius(), trueRange->getRadius()
            )
        );
    }
}