
#include <iostream>

#include <base/direction.hpp>
#include <entity/bullet/factory.hpp>
#include <entity/plant/factory.hpp>
#include <entity/plant/plant.hpp>
#include <entity/zombie/zombie.hpp>
#include <game.h>

using namespace std;
using namespace sf;
using namespace demo;

void test_simple_tool()
{
    Game game;
    // game.scene()->setBackGround(
    //     "/home/wlle/code/demo/sfml2/resource/background"
    // );
    game.setFrame(60);

    auto plant =
        PlantFactory::getFactory()->create("PeaShooter", {100, 100});
    if(!plant) {
        cout << "create bullet error\n";
        return;
    }
    game.scene()->addPlant(plant);

    auto zombie = new Zombie;
    zombie->addComp<CompType::MOVEMENT>(Direction::DIR::STOP, 1);
    zombie->addComp<CompType::POSITION>(
        PositionType{700, 100}, SizeType{50, 50}
    );
    zombie->addComp<CompType::ANIMATION>(
        "/home/wlle/code/demo/sfml2/resource/sun"
    );
    zombie->addComp<CompType::HP>(10);
    game.scene()->addZombie(zombie);

    game.run();
}

int main()
{
    cout << "start test" << endl;
    test_simple_tool();
    return 0;
}