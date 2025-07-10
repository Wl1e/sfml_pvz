
#include <iostream>
#include <thread>

#include <base/direction.hpp>
#include <entity/bullet/factory.hpp>
#include <entity/plant/factory.hpp>
#include <entity/tool/card.hpp>
#include <entity/tool/plant_creator.hpp>
#include <entity/tool/zombie_creator.hpp>
#include <game.h>

using namespace std;
using namespace sf;
using namespace demo;

Game game;

void initBackground()
{
    game.scene()->addBackGround(
        "/home/wlle/code/demo/sfml2/resource/Background.jpg",
        PositionType(0, 0),
        SizeType(game.scene()->getSize())
    );
}

void initPlant()
{
    auto pos = axis2pos({3, 2});
    cout << "[ " << pos.x << ' ' << pos.y << "]\n";
    auto plant = PlantFactory::getFactory()->create(
        "PeaShooter", sf::Vector2i(pos)
    );
    if(!plant) {
        cout << "create plant error\n";
        return;
    }
    game.scene()->addPlant(plant);
}

void initZombie()
{
    cout << "create zombie\n";
    auto zombiecreator = new ZombieCreator();
    zombiecreator->setCD(300);
    game.scene()->addTool(zombiecreator);
    // auto zombie =
    //     ZombieFactory::getFactory()->create("NormalZombie", 2);
    // if(!zombie) {
    //     cout << "create zombie error\n";
    //     return;
    // }

    // game.scene()->addZombie(zombie);
}

void initTool()
{
    auto plantCreator = new PlantCreator;
    plantCreator->init("PeaShooter", 0);
    game.scene()->addTool(plantCreator);
}

void simple_test()
{

    game.setFrame(60);
    // initBackground();
    cout << "finish create background\n";
    initTool();
    cout << "finish create tool\n";
    initPlant();
    cout << "finish create plant\n";
    initZombie();
    cout << "finish create zombie\n";

    // thread([&]() {
    //     this_thread::sleep_for(1s);
    //     createZombie();
    // }).detach();

    game.run();
}

int main()
{
    cout << "start test" << endl;
    simple_test();
    return 0;
}