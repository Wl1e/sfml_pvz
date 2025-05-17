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
        _delPlant(m_plants[pos_axis.x][pos_axis.y]);
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
    Plant* getPlantByAxis(const sf::Vector2i& axis_pos)
    {
        return m_plants[axis_pos.x][axis_pos.y];
    }
    const std::unordered_set<Zombie*>&
    getZombiesByPath(int path) const
    {
        return m_zombies[path];
    }
    bool isOpen() const;

private:
    void _initUI();
    bool _assertInThread() const;

    void _delPlant(Plant* plant);
    void _delZombie(Zombie* zombie);

    bool _checkClose(const sf::Event& event);

    void updateBackground();
    void updatePlants();
    void updateZombies();
    void updateBullets();

private:
    sf::RenderWindow* m_window;
    Entity* m_background;
    std::thread::id m_thread_id;

    std::unordered_set<Bullet*> m_bullets;
    std::vector<std::vector<Plant*>> m_plants;
    std::vector<std::unordered_set<Zombie*>> m_zombies;

    std::vector<sceneHandler> m_handler;
};

} // namespace demo
