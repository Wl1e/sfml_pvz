
#include <iostream>

#include <base/direction.hpp>
#include <entity/bullet/factory.hpp>
#include <entity/plant/factory.hpp>
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

    auto plant =
        PlantFactory::getFactory()->create("PeaShooter", {500, 330});
    if(!plant) {
        cout << "create plant error\n";
        return;
    }
    game.scene()->addPlant(plant);

    auto zombie = ZombieFactory::getFactory()->create("normal", 0);
    if(!zombie) {
        cout << "create zombie error\n";
        return;
    }

    // game.scene()->addZombie(zombie);

    game.run();
}

int main()
{
    cout << "start test" << endl;
    test_simple_tool();
    return 0;
}