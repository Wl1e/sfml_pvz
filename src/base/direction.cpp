#include <base/direction.hpp>

using namespace std;
using namespace sf;
using namespace demo;

Vector2f Direction::mask[] = {
    {0, 0}, {0, -1}, {0, 1}, {-1, 0}, {1, 0}
};
