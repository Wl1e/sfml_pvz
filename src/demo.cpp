
#include <iostream>

#include <entity/entity.hpp>
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
    auto t = new Entity();
    t->addComp<CompType::MOVEMENT>(
        Vector2i(0, 0), Vector2u{40, 40}, 1
    );
    t->addComp<CompType::ANIMATION>(
        "/home/wlle/code/demo/sfml2/resource/sun"
    );
    // t->setSize({10, 10});
    game.scene()->addEntity(t);

    game.run();
}

int main()
{
    cout << "start test" << endl;
    test_simple_tool();
    return 0;
}