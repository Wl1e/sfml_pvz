#include <animation/gamescene.h>
#include <base/tools.h>
#include <defines.h>
#include <entity/entity.hpp>

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
    m_background(nullptr), m_thread_id(this_thread::get_id())
{
    m_window->setKeyRepeatEnabled(false);
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

    // for(auto& func : m_handler) {
    //     func(this);
    // }
    // m_handler.clear();

    if(m_background) {
        m_background->updade();
    }
    for(auto entity : m_entitys) {
        entity->updade();
    }
    // for(auto tool : m_tools) {
    //     tool->update();
    // }
    // for(size_t idx = 0; idx < grass_path; ++idx) {
    //     for(auto plant : m_plants[idx]) {
    //         if(!plant) {
    //             continue;
    //         }
    //         plant->update();
    //     }
    // }
    // for(size_t idx = 0; idx < grass_path; ++idx) {
    //     for(auto zombie : m_zombies[idx]) {
    //         if(!zombie) {
    //             continue;
    //         }
    //         zombie->update();
    //     }
    // }
}

void GameScene::update()
{
    if(!assertInThread()) {
        return;
    }
    if(m_background) {
        m_background->updade();
    }
    for(auto entity : m_entitys) {
        entity->updade();
    }
    // for(auto tool : m_tools) {
    //     tool->update();
    // }
    // for(size_t idx = 0; idx < grass_path; ++idx) {
    //     for(auto plant : m_plants[idx]) {
    //         if(plant->isDied()) {
    //             delPlant(plant);
    //             continue;
    //         }
    //         if(!plant) {
    //             continue;
    //         }
    //         plant->update();
    //     }
    // }
}

void GameScene::run()
{
    optional<Event> event;
    while(m_window->isOpen()) {
        if(event = m_window->pollEvent(), event.has_value()) {
            m_window->clear();
            update(event.value());
            m_window->display();
        } else {
            m_window->clear();
            update();
            m_window->display();
        }
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

// void GameScene::addPlant(Plant* plant, const Vector2i& pos_axis)
// {
//     plant->setScene(this);
//     plant->setPlantPos(pos_axis);
//     m_plants[pos_axis.x][pos_axis.y] = plant;
// }

// void GameScene::addTool(Tool* tool, const Vector2i& pos)
// {
//     tool->setPos(pos);
//     tool->setScene(this);
//     m_tools.insert(tool);
// }

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

void GameScene::addEntity(Entity* entity)
{
    entity->setScene(this);
    m_entitys.push_back(entity);
}