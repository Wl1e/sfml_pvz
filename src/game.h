#pragma once

#include <vector>

#include <animation/gamescene.h>

namespace demo {

class Entity;

class Game
{
public:
    Game() : m_scene(new GameScene)
    {
    }
    ~Game()
    {
        delete m_scene;
    }

    void run()
    {
        m_scene->run();
    }

    void addEntity(Entity* entity)
    {
        m_scene->addEntity(entity);
    }
    void delEntity(Entity* entity)
    {
        m_scene->delEntity(entity);
    }

private:
    bool m_running;

    GameScene* m_scene;
    // std::vector<std::vector<Plant*>> m_plants;
    // std::vector<std::vector<Zombie*>> m_zombies;
    // std::vector<Tool*> m_Tools;
};

} // namespace demo