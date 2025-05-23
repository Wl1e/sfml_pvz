#include <entity/tool/spade.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void Spade::click(const Vector2i& pos)
{
    getScene()->delPlant(pos2axis(PositionType(pos)));
}