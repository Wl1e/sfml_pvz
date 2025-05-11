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

class GameEntity;

class GameScene
{
public:
    GameScene();
    ~GameScene();

    void run();
    void update(sf::Event event);
    void update();

    void addEntity(GameEntity* entity)
    {
        m_entitys.insert(entity);
    }
    void delEntity(GameEntity* entity)
    {
        m_entitys.erase(entity);
    }
    // void setCloseFunction(std::function<bool(const sf::Event&)>
    // func)
    // {
    //     m_close_func = std::move(func);
    // }
    Vector2u getSize() const;
    // bad
    sf::RenderWindow* getNativeWindow()
    {
        return m_window;
    }
    std::optional<sf::Event> getInput() const;
    const vector<GameEntity*>& getZombiesByPath(int path) const
    {
        return m_zombies[path];
    }
    const vector<vector<GameEntity*>>& getZombies() const
    {
        return m_zombies;
    }
    bool isOpen() const;

private:
    void initUI();
    bool assertInThread() const;

private:
    sf::RenderWindow* m_window;
    std::unordered_set<GameEntity*> m_entitys;
    vector<vector<GameEntity*>> m_plants;
    vector<vector<GameEntity*>> m_zombies;
    thread::id m_thread_id;

    // std::function<bool(const sf::Event&)> m_close_func;
};

} // namespace demo
