#include <entity/components/position_comp.hpp>

using namespace std;
using namespace sf;
using namespace demo;

Vector2i MovementComp::mask[] = {
    {0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};