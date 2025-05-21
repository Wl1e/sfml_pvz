#include <entity/too.h>

using namespace std;
using namespace sf;
using namespace demo;

void demo::moveUpdate(Tool* tool)
{
    tool->setPos(tool->getPos() + Vector2i(0, 1));
}