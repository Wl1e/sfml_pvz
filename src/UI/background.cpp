#include <unordered_map>

#include <animation/gamescene.hpp>
#include <UI/background.hpp>
#include <UI/defines.hpp>

using namespace std;
// using namespace sf;
using namespace demo;

const string backgroundPath =
    "/home/wlle/sfml2/resource/background/";

const SizeType FULL_SCREEN = SizeType(-1, -1);
const SizeType ADJUST_ANIMA = SizeType(-2, -2);

static const unordered_map<string, pair<PositionType, SizeType>>
    ELEMENTS = {
        {"Background.jpg", {PositionType(0, 0), FULL_SCREEN}},
        // {"Card.png",
        //  {PositionType(GRASS_START_X + 100, 10), SizeType(70,
        //  90)}},
        // {"Shop.png",
        //  {PositionType(GRASS_START_X, 0), SizeType(600, 110)}}
};

static vector<string> updateOrder{
    "Background.jpg", "Shop.png", "Card.png"
};

void BackgroundLayout::initScene(GameScene* scene)
{
    PositionType position;
    SizeType size;
    for(const auto& name : updateOrder) {
        if(ELEMENTS.find(name) == ELEMENTS.end()) {
            continue;
        }
        position = ELEMENTS.at(name).first;
        size = ELEMENTS.at(name).second;
        if(size == FULL_SCREEN) {
            size = SizeType(scene->getSize());
        }
        printf("%s\n", (backgroundPath + name).data());
        scene->addBackGround(backgroundPath + name, position, size);
    }
}