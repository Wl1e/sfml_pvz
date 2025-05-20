#include <iostream>
#include <thread>

#include <animation/gamescene.h>
#include <base/tools.h>
#include <defines.h>
#include <entity/attack.hpp>
#include <entity/background.hpp>
#include <entity/bullet/bullet.hpp>
#include <entity/frame.hpp>
#include <entity/plant/plant.hpp>
#include <entity/zombie/zombie.hpp>

using namespace std;
using namespace sf;
using namespace demo;

bool defaultCloseFunc(const Event& event)
{
    if(event.is<Event::KeyPressed>()) {
        auto keyPressedEvent = event.getIf<Event::KeyPressed>();
        if(keyPressedEvent->code == Keyboard::Key::Escape) {
            return true;
        }
    }
    return false;
}

GameScene::GameScene() :
    m_window(new sf::RenderWindow(
        VideoMode({800, 600}), "game", State::Windowed
    )),
    m_background(nullptr), m_thread_id(this_thread::get_id()),
    m_plants(6, vector<Plant*>(9, nullptr)),
    m_zombies(6, vector<Zombie*>())
{
    m_window->setKeyRepeatEnabled(false);
}

GameScene::~GameScene()
{
}

bool GameScene::_assertInThread() const
{
    return m_thread_id == this_thread::get_id();
}

// FIXME: 两个update过于重复
void GameScene::update(Event event)
{
    if(!_assertInThread()) {
        return;
    }

    for(auto& func : m_handler) {
        func(this);
    }
    m_handler.clear();

    _updateBackground();
    _updateBullets();
    _updatePlants();
    _updateZombies();
}

void GameScene::update()
{
    if(!_assertInThread()) {
        return;
    }

    for(auto& func : m_handler) {
        func(this);
    }
    m_handler.clear();

    _updateBackground();
    _updateBullets();
    _updatePlants();
    _updateZombies();
}

void GameScene::_updateBackground()
{
    if(m_background) {
        m_background->updade();
    }
}

void GameScene::_updatePlants()
{
    for(auto& plants : m_plants) {
        for(auto plant : plants) {
            if(!plant) {
                continue;
            }
            plant->updade();
        }
    }
}
void GameScene::_updateZombies()
{
    for(auto& zombies : m_zombies) {
        for(auto zombie : zombies) {
            zombie->updade();
        }
    }
}

void GameScene::_updateBullets()
{
    for(auto bullet : m_bullets) {
        bullet->updade();
    }
}

void GameScene::run()
{
    optional<Event> event;
    while(m_window->isOpen()) {

        FrameManager::getInstance().update();
        cout << "frame: " << FrameManager::getInstance().getFrame()
             << '\n';

        if(event = m_window->pollEvent(), event.has_value()) {
            cout << "click\n";
            if(_checkClose(event.value())) {
                m_handler.push_back([](GameScene* scene) {
                    scene->close();
                });
            }
        }

        m_window->clear();
        update();
        m_window->display();
    }
}

Vector2u GameScene::getSize() const
{
    return m_window->getSize();
}

bool GameScene::isOpen() const
{
    return m_window->isOpen();
}

void GameScene::setBackGround(std::string_view path)
{
    m_background =
        new Background(path, Vector2i(0, 0), m_window->getSize());
    m_background->setScene(this);
}

void GameScene::addPlant(Plant* plant)
{
    plant->setScene(this);
    auto& plantPos = getEntityPosition(plant);
    auto axis_pos = pos2axis(plantPos);
    m_plants[axis_pos.y][axis_pos.x] = plant;
}

void GameScene::addZombie(Zombie* zombie)
{
    zombie->setScene(this);
    auto& zombiePos = getEntityPosition(zombie);
    m_zombies[getPath(zombiePos)].push_back(zombie);
}
void GameScene::addBullet(Bullet* bullet)
{
    bullet->setScene(this);
    m_bullets.insert(bullet);
}

void GameScene::_delPlant(Plant* plant)
{
    if(plant == nullptr) {
        return;
    }
    delete plant;
}
void GameScene::_delZombie(Zombie* zombie)
{
}
void GameScene::_delBullet(Bullet* bullet)
{
    // error
    // m_bullets.erase(bullet);
}

bool GameScene::_checkClose(const Event& event)
{
    if(event.is<Event::KeyPressed>()) {
        if(event.getIf<Event::KeyPressed>()->code
           == Keyboard::Key::Escape) {
            return true;
        }
    }
    return false;
}

void GameScene::close()
{
    m_window->close();
}
