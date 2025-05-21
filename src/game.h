#pragma once

#include <vector>

#include <animation/gamescene.hpp>
#include <base/tools.hpp>

namespace demo {

class FrameTimerQueue;

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

    GameScene* scene()
    {
        return m_scene;
    }
    void setFrame(int frame)
    {
        // 不够准确
        // internal() = milliseconds(1000 / frame);
        m_scene->getNativeWindow()->setFramerateLimit(frame);
    }

private:
    bool m_running;

    GameScene* m_scene;
};

} // namespace demo