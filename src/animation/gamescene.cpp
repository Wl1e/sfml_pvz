#include <thread>

#include <animation/gamescene.h>
#include <base/tools.h>
#include <defines.h>
#include <entity/attack.hpp>
#include <entity/bullet/bullet.hpp>
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
    m_plants(6, vector<Plant*>(9, nullptr))
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

    if(m_background) {
        m_background->updade();
    }

    for(auto& plants : m_plants) {
        for(auto plant : plants) {
            if(!plant) {
                continue;
            }
            plant->updade();
        }
    }
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

    updateBackground();
    updateBullets();
    updatePlants();
    updateZombies();
}

void GameScene::updateBackground()
{
    if(m_background) {
        m_background->updade();
    }
}

void GameScene::updatePlants()
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
void GameScene::updateZombies()
{
}
void GameScene::updateBullets()
{
    sf::Vector2i bullet_pos;
    for(auto bullet : m_bullets) {
        bullet_pos = getEntityPosition(bullet);
        auto& zombies = getZombiesByPath(pos2axis(bullet_pos).x);
        for(auto zombie : zombies) {
            if(overlay(bullet, zombie)) {
                bulletAttackZombie(bullet, zombie);
            }
        }
    }
}

void GameScene::run()
{
    optional<Event> event;
    while(m_window->isOpen()) {
        m_window->clear();
        if(event = m_window->pollEvent(), event.has_value()) {
            if(_checkClose(event.value())) {
                m_window->close();
                break;
            }
            update(event.value());
        } else {
            update();
        }
        m_window->display();
        // wait();
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
    m_background = new Entity();
    m_background->addComp<CompType::POSITION>(
        Vector2i(0, 0), m_window->getSize()
    );
    m_background->addComp<CompType::ANIMATION>(
        "/home/wlle/code/demo/sfml2/resource/background"
    );
    m_background->setScene(this);
}

void GameScene::addPlant(Plant* plant)
{
    plant->setScene(this);
    auto& plantPos = getEntityPosition(plant);
    auto axis_pos = pos2axis(plantPos);
    m_plants[axis_pos.x][axis_pos.y] = plant;
}

void GameScene::addZombie(Zombie* zombie)
{
    zombie->setScene(this);
    auto& zombiePos = getEntityPosition(zombie);
    m_zombies[zombiePos.x].insert(zombie);
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