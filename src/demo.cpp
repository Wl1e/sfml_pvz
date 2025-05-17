
#include <iostream>

#include <base/direction.hpp>
#include <entity/bullet/bullet.hpp>
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

    auto bullet = new Bullet(
        {100,
         Vector2i(100, 100),
         Vector2u(10, 10),
         false,
         Direction::DIR::RIGHT,
         10000,
         1,
         "/home/wlle/code/demo/sfml2/resource/sun"}
    );
    game.scene()->addBullet(bullet);

    auto zombie = new Zombie;
    zombie->addComp<CompType::MOVEMENT>(Direction::DIR::STOP, 1);
    zombie->addComp<CompType::POSITION>(
        Vector2i{700, 100}, Vector2u{10, 10}
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