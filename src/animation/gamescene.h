#pragma once

#include <functional>
#include <memory>
#include <thread>
#include <unordered_set>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

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

// TODO: 换个好名字
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

    void addPlant(Plant* plant);
    void addZombie(Zombie* zombie);
    void addHander(sceneHandler handler)
    {
        m_handler.emplace_back(std::move(handler));
    }

    void delPlant(const sf::Vector2i& pos_axis)
    {
        delPlant(m_plants[pos_axis.x][pos_axis.y]);
        m_plants[pos_axis.x][pos_axis.y] = nullptr;
    }

    sf::Vector2u getSize() const;
    // FIXME: bad
    sf::RenderWindow* getNativeWindow()
    {
        return m_window;
    }
    const std::vector<std::vector<Plant*>>& getAllPlants() const
    {
        return m_plants;
    }
    const std::vector<Zombie*>& getAllZombies() const
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
    Entity* m_background;
    std::thread::id m_thread_id;
    // std::vector<Entity*> m_entitys;
    // std::unordered_set<Tool*> m_tools;
    std::vector<std::vector<Plant*>> m_plants;
    std::vector<Zombie*> m_zombies;

    std::vector<sceneHandler> m_handler;
};

} // namespace demo
