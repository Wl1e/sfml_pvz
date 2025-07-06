
#include <iostream>
#include <thread>

#include <base/direction.hpp>
#include <entity/bullet/factory.hpp>
#include <entity/plant/factory.hpp>
#include <entity/tool/plant_creator.hpp>
#include <entity/zombie/factory.hpp>
#include <game.h>

using namespace std;
using namespace sf;
using namespace demo;

Game game;

void createPlant()
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

void createZombie()
{
    cout << "create zombie\n";
    auto zombie =
        ZombieFactory::getFactory()->create("NormalZombie", 2);
    if(!zombie) {
        cout << "create zombie error\n";
        return;
    }

    game.scene()->addZombie(zombie);
}

void createTool()
{
    auto plantCreator = new PlantCreator("PeaShooter");
    game.scene()->addTool(plantCreator);
}

void simple_test()
{
    game.scene()->setBackGround(
        "/home/wlle/code/demo/sfml2/resource/Background.jpg"
    );
    game.setFrame(60);

    createTool();
    cout << "finish create tool\n";
    createPlant();
    cout << "finish create plant\n";
    createZombie();
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