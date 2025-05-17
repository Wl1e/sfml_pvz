
#include <iostream>

#include <base/direction.hpp>
#include <entity/plant/plant.hpp>
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

    auto t = new Plant;
    t->addComp<CompType::MOVEMENT>(Direction::DIR::RIGHT, 1);
    t->addComp<CompType::POSITION>(
        Vector2i{100, 100}, Vector2u{10, 10}
    );
    t->addComp<CompType::ANIMATION>(
        "/home/wlle/code/demo/sfml2/resource/sun"
    );
    game.scene()->addPlant(t);

    game.run();
}

int main()
{
    cout << "start test" << endl;
    test_simple_tool();
    return 0;
}