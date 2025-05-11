#include <animation/gamescene.h>
#include <base/tools.hpp>
#include <defines.h>
#include <main/entity.h>
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
    m_thread_id(this_thread::get_id())
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
}

void GameScene::update()
{
    if(!assertInThread()) {
        return;
    }
    for(auto& a : m_entitys) {
        a->update(nullptr);
    }
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