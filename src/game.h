#pragma once

#include <vector>

#include <animation/gamescene.h>

namespace demo {

class Entity;
class Plant;
class Zombie;
class Tool;
class Bullet;

class Game
{
    Game();
    ~Game();

    void addEntity(Entity* entity);
    void delEntity(Entity* entity);

    void update();

    const std::vector<Zombie*> getZombiesByPath(int path);

private:
    bool m_running;

    GameScene* m_scene;
    // std::vector<std::vector<Plant*>> m_plants;
    // std::vector<std::vector<Zombie*>> m_zombies;
    // std::vector<Tool*> m_Tools;
};

} // namespace demo