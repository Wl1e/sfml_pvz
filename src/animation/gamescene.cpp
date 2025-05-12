#include <animation/gamescene.h>
#include <base/tools.hpp>
#include <defines.h>
#include <entity/plant.h>
#include <entity/tool.h>
#include <entity/zombie.h>

#include <thread>

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
    m_thread_id(this_thread::get_id()),
    m_plants(6, vector<Plant*>(9, nullptr))
{
}

GameScene::~GameScene()
{
}

bool GameScene::assertInThread() const
{
    return m_thread_id == this_thread::get_id();
}

void GameScene::update(Event event)
{
    if(!assertInThread()) {
        return;
    }
    for(size_t idx = 0; idx < grass_path; ++idx) {
        for(auto plant : m_plants[idx]) {
            plant->update();
        }
    }
    for(size_t idx = 0; idx < grass_path; ++idx) {
        for(auto zombie : m_zombies[idx]) {
            zombie->update();
        }
    }
}

void GameScene::update()
{
    // if(!assertInThread()) {
    //     return;
    // }
    // for(auto& a : m_entitys) {
    //     a->update();
    // }
}

void GameScene::run()
{
    optional<Event> event;
    while(m_window->isOpen()) {
        while(event = m_window->pollEvent(), event.has_value()) {
            m_window->clear();
            update(event.value());
            m_window->display();
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

optional<Event> GameScene::getInput() const
{
    return m_window->pollEvent();
}

bool GameScene::isOpen() const
{
    return m_window->isOpen();
}

void GameScene::addEntity(Entity* entity)
{
}
void GameScene::delEntity(Entity* entity)
{
}

void GameScene::addPlant(Plant* plant, const Vector2i& pos_axis)
{
    plant->setPos(axis2pos(pos_axis));
    plant->setScene(this);
    m_plants[pos_axis.x][pos_axis.y] = (plant);
}

void GameScene::addTool(Tool* tool, const Vector2i& pos)
{
    tool->setPos(pos);
    tool->setScene(this);
    m_tools.insert(tool);
}