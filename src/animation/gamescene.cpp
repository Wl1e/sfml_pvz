#include <thread>

#include <animation/gamescene.h>
#include <base/tools.h>
#include <defines.h>
#include <entity/plant/plant.hpp>
#include <entity/zombie.hpp>

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
    m_plants(9, vector<Plant*>(9, nullptr))
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

    // for(auto& func : m_handler) {
    //     func(this);
    // }
    // m_handler.clear();

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
    auto& plantPos = getEntityPosition(zombie);
    m_zombies.push_back(zombie);
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