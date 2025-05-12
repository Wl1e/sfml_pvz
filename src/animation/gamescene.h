#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <thread>
#include <unordered_set>

// namespace sf {
// class RenderWindow;
// } // namespace sf

namespace demo {

class Entity;

class GameScene
{
public:
    GameScene();
    ~GameScene();

    void run();
    void update(sf::Event event);
    void update();

    void addEntity(Entity* entity)
    {
        m_entitys.insert(entity);
    }
    void delEntity(Entity* entity)
    {
        m_entitys.erase(entity);
    }
    // void setCloseFunction(std::function<bool(const sf::Event&)>
    // func)
    // {
    //     m_close_func = std::move(func);
    // }
    sf::Vector2u getSize() const;
    // bad
    sf::RenderWindow* getNativeWindow()
    {
        return m_window;
    }
    std::optional<sf::Event> getInput() const;
    const std::vector<Entity*>& getZombiesByPath(int path) const
    {
        return m_zombies[path];
    }
    const std::vector<std::vector<Entity*>>& getZombies() const
    {
        return m_zombies;
    }
    bool isOpen() const;

private:
    void initUI();
    bool assertInThread() const;

private:
    sf::RenderWindow* m_window;
    std::unordered_set<Entity*> m_entitys;
    std::vector<std::vector<Entity*>> m_plants;
    std::vector<std::vector<Entity*>> m_zombies;
    std::thread::id m_thread_id;

    // std::function<bool(const sf::Event&)> m_close_func;
};

} // namespace demo
