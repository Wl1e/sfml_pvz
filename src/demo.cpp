
#include <iostream>

#include <entity/tool.h>
#include <game.h>

using namespace std;
using namespace sf;
using namespace demo;

void test_simple_tool()
{
    cout << "here" << endl;
    Game game;
    game.scene()->setBackGround(
        "/home/wlle/code/demo/sfml2/source/background"
    );
    game.setFrame(144);
    auto t = new Tool();
    t->setAniamtion<Animation>(
        "/home/wlle/code/demo/sfml2/source/sun"
    );
    // t->setSize({10, 10});

    cout << t->getSize().x << ' ' << t->getSize().y << '\n';

    game.scene()->addTool(t, {20, 20});
    game.run();
}

int main()
{
    cout << "start test" << endl;
    test_simple_tool();
    return 0;
}