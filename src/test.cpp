
#include <iostream>
#include <thread>

#include <SFML/System/Sleep.hpp>
#include <animation/base.h>
#include <main/game.h>
#include <main/tools.h>

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
    game.addEntity(t);
    t->setPostion({0, 0});
    t->setAnimation("source/");

    return 0;
}