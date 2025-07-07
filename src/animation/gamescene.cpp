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
#include <event_manager.hpp>
#include <system/init.hpp>
#include <UI/background.hpp>
#include <UI/defines.hpp>
#include <UI/ui_layout.hpp>

using namespace std;
using namespace sf;
using namespace demo;

/**
 * TODO:
 * 这个文件太大了
 * 后续可以根据图像和逻辑进行拆分
 */

GameScene::GameScene() :
    m_window(new sf::RenderWindow(
        VideoMode({UI_DEFINE::WINDOW_LENGTH, UI_DEFINE::WINDOW_WIDE}
        ),
        "game",
        State::Windowed
    )),
    m_thread_id(this_thread::get_id()),
    m_plants(
        UI_DEFINE::GRASS_PATH,
        vector<Plant*>(UI_DEFINE::GRASS_COUNT, nullptr)
    ),
    m_zombies(6, unordered_set<Zombie*>())
{
    m_window->setKeyRepeatEnabled(false);

    initSystems();
    BackgroundLayout::initScene(this);
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

    auto lines = UILayout().display();
    draw(lines);

    updateSystems();

    _updateTools();
    _updateBullets();
    _updatePlants();
    _updateZombies();
}

void GameScene::_updateBackground()
{
    for(auto bg : m_backgrounds) {
        bg->update();
    }
}

void GameScene::_updatePlants()
{
    for(auto& plants : m_plants) {
        for(auto plant : plants) {
            if(!plant) {
                continue;
            }
            plant->update();
        }
    }
}
void GameScene::_updateZombies()
{
    for(auto& zombies : m_zombies) {
        for(auto zombie : zombies) {
            zombie->update();
        }
    }
}

void GameScene::_updateBullets()
{
    for(auto bullet : m_bullets) {
        bullet->update();
    }
}

void GameScene::_updateTools()
{
    for(auto tool : m_tools) {
        tool->update();
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

void GameScene::addBackGround(
    std::string_view path,
    const PositionType& position,
    const SizeType& size
)
{
    auto background = new Background();
    background->init(path, position, size);
    background->setScene(this);
    m_backgrounds.push_back(background);
    printf("add backfround %s success\n", path.data());
}

void GameScene::addPlant(Plant* plant)
{
    plant->setScene(this);
    auto axis_pos = pos2axis(getEntityPosition(plant));
    // FIXME: 后续南瓜罩出现需要改
    if(!m_plants[axis_pos.y][axis_pos.x]) {
        m_plants[axis_pos.y][axis_pos.x] = plant;
    }
    printf("add plant: %p\n", plant);
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
    printf("add zombie: %p\n", zombie);
}
void GameScene::addBullet(Bullet* bullet)
{
    bullet->setScene(this);
    m_bullets.insert(bullet);
    printf("add bullet: %p\n", bullet);
}
void GameScene::addTool(Tool* tool)
{
    tool->setScene(this);
    m_tools.insert(tool);
    printf("add tool: %p\n", tool);
}

void GameScene::click(const sf::Vector2i& pos)
{
    if(m_hand) {
        m_hand->use(pos);
        m_hand = nullptr;
        return;
    }
    PositionType clickPos = PositionType(pos);
    for(auto tool : m_tools) {
        if(auto position = tool->getComp<CompType::POSITION>();
           position && position->clicked(clickPos)) {
            m_hand = tool;
            printf("select tool %p\n", tool);
            trigger(
                m_hand, EventType::Click, make_any<sf::Vector2i>(pos)
            );
        }
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

void GameScene::_delPlant(Plant* plant)
{
    if(plant == nullptr) {
        return;
    }
    delete plant;
    // printf("del plant\n");
}
void GameScene::_delZombie(Zombie* zombie)
{
    if(auto pos = zombie->getComp<CompType::POSITION>(); pos) {
        m_zombies[getPath(pos->getPos())].erase(zombie);
        delete zombie;
        // printf("del zombie\n");
    }
}
void GameScene::_delBullet(Bullet* bullet)
{
    // error
    m_bullets.erase(bullet);
    delete bullet;
    printf("del bullet\n");
}

void GameScene::delPlant(const sf::Vector2i& pos_axis)
{
    _delPlant(getPlantByAxis(pos_axis));
    m_plants[pos_axis.y][pos_axis.x] = nullptr;
}
void GameScene::delBullet(Bullet* bullet)
{
    if(m_bullets.find(bullet) != m_bullets.end()) {
        _delBullet(bullet);
    }
}
void GameScene::delZombie(Zombie* zombie)
{
    _delZombie(zombie);
}
void GameScene::delEntity(Entity* entity)
{
    if(isPlant(entity)) {
        assert(entity->hasComp(CompType::POSITION));
        delPlant(entity->getComp<CompType::POSITION>()->getAxisPos()
        );
    } else if(isZombie(entity)) {
        delZombie(dynamic_cast<Zombie*>(entity));
    } else if(isBullet(entity)) {
        delBullet(dynamic_cast<Bullet*>(entity));
    } else {
        printf(
            "del entity error, entity name is %s, type is %d, addr "
            "is %p\n",
            entity->getName().data(),
            entity->getStatus(),
            entity
        );
    }
}

void GameScene::draw(const sf::Drawable& object) const
{
    m_window->draw(object);
}
void GameScene::draw(const BaseRange* obejct) const
{
    m_window->draw(*(obejct->getShape()));
}

void GameScene::_initUI()
{
    Background* shop = new Background();
}