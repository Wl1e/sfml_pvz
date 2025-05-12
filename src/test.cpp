
#include <iostream>

#include <SFML/System/Sleep.hpp>
#include <animation/base.h>
#include <entity/tool.h>
#include <game.h>

using namespace std;
using namespace sf;
using namespace demo;

void test_simple_tool()
{
}

int main()
{

    Game game;
    auto t = new Tool();
    // t->setAniamtion("source/sun");
    // game.addEntity(t);
    // t->setPos({0, 0});
    game.run();

    return 0;
}