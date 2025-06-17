
#include <iostream>

#include <base/direction.hpp>
#include <entity/bullet/factory.hpp>
#include <entity/plant/factory.hpp>
#include <entity/tool/plant_creator.hpp>
#include <entity/zombie/factory.hpp>
#include <game.h>

using namespace std;
using namespace sf;
using namespace demo;

void test_simple_tool()
{
    Game game;
    game.scene()->setBackGround(
        "/home/wlle/code/demo/sfml2/resource/Background.jpg"
    );
    game.setFrame(60);

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

    cout << "create zombie\n";
    auto zombie = ZombieFactory::getFactory()->create("normal", 2);
    if(!zombie) {
        cout << "create zombie error\n";
        return;
    }

    game.scene()->addZombie(zombie);

    auto plantCreator = new PlantCreator("PeaShooter");
    game.scene()->addTool(plantCreator);

    game.run();
}

int main()
{
    cout << "start test" << endl;
    test_simple_tool();
    return 0;
}