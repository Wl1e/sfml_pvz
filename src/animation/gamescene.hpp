#pragma once

#include <functional>
#include <memory>
#include <thread>
#include <unordered_set>

#include <entity/entity.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace demo {

class Animation;
class Background;
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
    void update();
    void setBackGround(std::string_view path);

    void addPlant(Plant* plant);
    void addZombie(Zombie* zombie);
    void addBullet(Bullet* bullet);
    void addHander(sceneHandler handler)
    {
        m_handler.emplace_back(std::move(handler));
    }

    void delPlant(const sf::Vector2i& pos_axis);
    void delBullet(Bullet* bullet);
    void delZombie(Zombie* zombie);
    void delEntity(Entity*);

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
        if(axis_pos.y < 0 || axis_pos.y >= GRASS_PATH
           || axis_pos.x < 0 || axis_pos.x >= GRASS_COUNT) {
            return nullptr;
        }
        return m_plants[axis_pos.y][axis_pos.x];
    }
    const std::vector<Zombie*>& getZombiesByPath(int path) const
    {
        return m_zombies[path];
    }
    const std::vector<std::vector<Zombie*>>& getAllzombies() const
    {
        return m_zombies;
    }
    // std::vector<Entity*> getEntityInRange(EntityType,
    // AttackRange*);
    Tool* getHand() const
    {
        return m_hand;
    }

    void click(const sf::Vector2i& pos);

    bool isOpen() const;

    void draw(sf::Drawable& object)
    {
        m_window->draw(object);
    }

private:
    void _initUI();
    bool _assertInThread() const;
    void _handleEvent();

    void _delPlant(Plant* plant);
    void _delZombie(Zombie* zombie);
    void _delBullet(Bullet* bullet);

    void _updateBackground();
    void _updatePlants();
    void _updateZombies();
    void _updateBullets();

private:
    sf::RenderWindow* m_window;
    Background* m_background;
    std::thread::id m_thread_id;

    std::unordered_set<Bullet*> m_bullets;
    std::vector<std::vector<Plant*>> m_plants;
    std::vector<std::vector<Zombie*>> m_zombies;
    std::unordered_set<Tool*> m_tools;

    std::vector<sceneHandler> m_handler;

    Tool* m_hand;
};

} // namespace demo
