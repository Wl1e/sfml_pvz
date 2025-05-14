#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <memory>
#include <thread>
#include <unordered_set>

// namespace sf {
// class RenderWindow;
// } // namespace sf

namespace demo {

class Animation;
class Entity;
class Plant;
class Zombie;
class Tool;
class Bullet;
class GameScene;

// fixme: 换个好名字
using sceneHandler = std::function<void(GameScene*)>;

class GameScene
{
public:
    GameScene();
    ~GameScene();

    void run();
    void update(sf::Event event);
    void update();

    void setBackGround(std::string_view path);
    void addPlant(Plant* plant, const sf::Vector2i& pos_axis);
    void addZombie(Zombie* zombie);
    void addTool(Tool* tool, const sf::Vector2i& pos);
    void addHander(sceneHandler handler)
    {
        m_handler.emplace_back(std::move(handler));
    }

    void delPlant(const sf::Vector2i& pos_axis)
    {
        auto plant = m_plants[pos_axis.x][pos_axis.y];
        delPlant(plant);
    }

    sf::Vector2u getSize() const;
    // bad
    sf::RenderWindow* getNativeWindow()
    {
        return m_window;
    }
    const std::vector<Zombie*>& getZombiesByPath(int path) const
    {
        return m_zombies[path];
    }
    const std::vector<std::vector<Zombie*>>& getZombies() const
    {
        return m_zombies;
    }
    bool isOpen() const;

private:
    void initUI();
    bool assertInThread() const;

    void delPlant(Plant* plant);
    void delZombie(Zombie* zombie);

private:
    sf::RenderWindow* m_window;
    BaseAnimation* m_background;
    std::thread::id m_thread_id;
    std::unordered_set<Tool*> m_tools;
    std::vector<std::vector<Plant*>> m_plants;
    std::vector<std::vector<Zombie*>> m_zombies;

    std::vector<sceneHandler> m_handler;
};

} // namespace demo
