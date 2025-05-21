
#include <iostream>

#include <base/direction.hpp>
#include <entity/bullet/factory.hpp>
#include <entity/plant/plant.hpp>
#include <entity/zombie/zombie.hpp>
#include <game.h>

using namespace std;
using namespace sf;
using namespace demo;

void test_simple_tool()
{
    Game game;
    game.scene()->setBackGround(
        "/home/wlle/code/demo/sfml2/resource/background"
    );
    game.setFrame(144);

    auto bullet = BulletFactory::getFactory()->create(
        "Pea",
        {100,
         PositionType(100, 100),
         Direction(Direction::DIR::RIGHT),
         10000}
    );
    if(!bullet) {
        cout << "create bullet error\n";
        return;
    }
    game.scene()->addBullet(bullet);

    auto zombie = new Zombie;
    zombie->addComp<CompType::MOVEMENT>(Direction::DIR::STOP, 1);
    zombie->addComp<CompType::POSITION>(
        PositionType{700, 100}, SizeType{10, 10}
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