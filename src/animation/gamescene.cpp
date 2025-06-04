#include <iostream>
#include <thread>

#include <animation/event_handler.hpp>
#include <animation/gamescene.hpp>
#include <base/tools.hpp>
#include <entity/attack.hpp>
#include <entity/background.hpp>
#include <entity/bullet/bullet.hpp>
#include <entity/frame.hpp>
#include <entity/plant/plant.hpp>
#include <entity/tool/tool.hpp>
#include <entity/zombie/zombie.hpp>
#include <UI/defines.hpp>

using namespace std;
using namespace sf;
using namespace demo;

// bool defaultCloseFunc(const Event::Closed& event)
// {
//     if(event.is<Event::KeyPressed>()) {
//         auto keyPressedEvent = event.getIf<Event::KeyPressed>();
//         if(keyPressedEvent->code == Keyboard::Key::Escape) {
//             return true;
//         }
//     }
//     return false;
// }

GameScene::GameScene() :
    m_window(new sf::RenderWindow(
        VideoMode({UI_DEFINE::WINDOW_LENGTH, UI_DEFINE::WINDOW_WIDE}
        ),
        "game",
        State::Windowed
    )),
    m_background(nullptr), m_thread_id(this_thread::get_id()),
    m_plants(
        UI_DEFINE::GRASS_PATH,
        vector<Plant*>(UI_DEFINE::GRASS_COUNT, nullptr)
    ),
    m_zombies(6, unordered_set<Zombie*>())
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

void GameScene::_handleEvent()
{
    m_window->handleEvents(
        bind(
            &EventHandler::OnKeyPressed, m_window, placeholders::_1
        ),
        bind(&EventHandler::OnClosed, m_window, placeholders::_1),
        bind(
            &EventHandler::OnMouseButtonPressed,
            this,
            placeholders::_1
        ),
        bind(
            &EventHandler::OnMouseButtonReleased,
            this,
            placeholders::_1
        )
    );
}

void GameScene::run()
{
    optional<Event> event;
    while(m_window->isOpen()) {

        FrameManager::getInstance().update();
        // cout << "frame: " <<
        // FrameManager::getInstance().getFrame()
        //      << '\n';

        _handleEvent();

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
    m_background = new Background(
        path, PositionType(0, 0), SizeType(m_window->getSize())
    );
    m_background->setScene(this);
}

void GameScene::addPlant(Plant* plant)
{
    plant->setScene(this);
    auto axis_pos = pos2axis(getEntityPosition(plant));
    m_plants[axis_pos.y][axis_pos.x] = plant;
}

void GameScene::addZombie(Zombie* zombie)
{
    zombie->setScene(this);
    auto path = getPath(getEntityPosition(zombie));
    printf("zombie path: %d\n", path);
    if(path >= UI_DEFINE::GRASS_PATH) {
        return;
    }
    m_zombies[path].insert(zombie);
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
    if(auto pos = zombie->getComp<CompType::POSITION>(); pos) {
        m_zombies[getPath(pos->getPos())].erase(zombie);
    }
}
void GameScene::_delBullet(Bullet* bullet)
{
    // error
    m_bullets.erase(bullet);
}

void GameScene::click(const sf::Vector2i& pos)
{
    if(m_hand) {
        m_hand->click(pos);
        m_hand = nullptr;
        return;
    }
    PositionType clickPos = PositionType(pos);
    for(auto tool : m_tools) {
        if(!tool->hasComp(CompType::POSITION)) {
            continue;
        }
        if(!tool->getComp<CompType::POSITION>()->clicked(clickPos)) {
            continue;
        }
        m_hand = tool;
        break;
    }

    // try plants or zombies?
    // if(!target) {
    //     auto plant = getPlantByAxis(pos2axis(clickPos));
    //     if(plant && plant->hasComp(CompType::POSITION)
    //        && plant->getComp<CompType::POSITION>()->clicked(
    //            clickPos
    //        )) {
    //         target = plant;
    //     }
    // }
}

void GameScene::delPlant(const sf::Vector2i& pos_axis)
{
    _delPlant(getPlantByAxis(pos_axis));
    m_plants[pos_axis.y][pos_axis.x] = nullptr;
}
void GameScene::delBullet(Bullet* bullet)
{
    if(m_bullets.find(bullet) != m_bullets.end()) {
        m_bullets.erase(bullet);
    }
}
void GameScene::delZombie(Zombie* zombie)
{
    if(auto pos = zombie->getComp<CompType::POSITION>();
       pos != nullptr) {
        m_zombies[getPath(pos->getPos())].erase(zombie);
    }
}
void GameScene::delEntity(Entity* entity)
{
    if(isPlant(entity)) {
        assert(entity->hasComp(CompType::POSITION));
        delPlant(entity->getComp<CompType::POSITION>()->getAxisPos()
        );
    } else if(isZombie(entity)) {
        _delZombie(dynamic_cast<Zombie*>(entity));
    } else if(isBullet(entity)) {
        _delBullet(dynamic_cast<Bullet*>(entity));
    } else {
        // ...
    }
}

// vector<Entity*>
// GameScene::getEntityInRange(EntityType type, AttackRange* range)
// {
//     vector<Entity*> res;
//     if(type == EntityType::PLANT) {
//         auto trueRange = get_if<RectangleShape>(range);
//         if(trueRange) {}
//     } else if(type == EntityType::BULLET) {

//     } else if(type == EntityType::ZOMBIE) {
//     }
//     return res;
// }