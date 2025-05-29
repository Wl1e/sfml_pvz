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

template<class T>
void AttackRange<T>::display(GameScene* scene)
{
    scene->draw(m_range);
}

void PlantGetEnemys(
    const AttackRange<RectangleShape>& range,
    Entity* entity,
    vector<Entity*>& res
)
{
    // 杨桃、三线?
    float degree = range.getRotationDegrees();
    float int_degree;
    float value = modf(degree, &int_degree);

    vector<Zombie*> enemys;
    // 纯直线（优化）
    if(value == 0. && static_cast<int>(int_degree) % 180 == 0) {
        enemys = entity->getScene()->getZombiesByPath(
            getPath(range.getPosition())
        );
        for(auto enemy : enemys) {
            if(range.inRange(enemy)) {
                res.push_back(enemy);
            }
        }
    } else {
        // 另类攻击范围
        auto all_zombies = entity->getScene()->getAllzombies();
        for(auto entitys : all_zombies) {
            for(auto enemy : entitys) {
                if(range.inRange(enemy)) {
                    res.push_back(enemy);
                }
            }
        }
    }
}

template<class T>
void bulletGetEnemys(
    const AttackRange<T>& range, Entity* entity, vector<Entity*>& res
)
{
    auto enemys = entity->getScene()->getZombiesByPath(
        getPath(range.getPosition())
    );
    for(auto enemy : enemys) {
        if(range.inRange(enemy)) {
            res.push_back(enemy);
        }
    }
}

template<class T>
void zombieGetEnemys(
    const AttackRange<T>& range, Entity* entity, vector<Entity*>& res
)
{
    auto auto enemys = entity->getScene()->getPlantByAxis(
        pos2axis(range.getPosition())
    );
    if(range.inRange(enemys)) {
        res.push_back(enemys);
    }
}

template<class T>
std::vector<Entity*> AttackRange<T>::getEnemyInRange(Entity* entity)
{
    std::vector<Entity*> res;

    auto scene = entity->getScene();
    if(isZombie(entity)) {
        // TODO: 一个格子可能有多个植物
        zombieGetEnemys(this, entity, res);
    } else if(isBullet(entity)) {
        bulletGetEnemys(this, entity, res);
    } else if(isPlant(entity)) {
        PlantGetEnemys(this, entity, res);
    }
    return res;
}

bool AttackRange<RectangleShape>::_inRange(Entity* entity) const
{
    assert(entity->hasComp(CompType::POSITION));
    auto pos = entity->getComp<CompType::POSITION>();
    return m_range.getGlobalBounds()
        .findIntersection(pos->getHitbox().getGlobalBounds())
        .has_value();
}

template class AttackRange<sf::CircleShape>;
template class AttackRange<sf::RectangleShape>;