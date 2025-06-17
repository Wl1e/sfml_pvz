#include <animation/gamescene.hpp>
#include <entity/plant/factory.hpp>
#include <entity/tool/plant_creator.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void PlantCreator::click(const Vector2i& pos)
{
    auto newPlant = PlantFactory::getFactory()->create(m_plant, pos);
    getScene()->addPlant(newPlant);
}

void PlantCreator::_initComp()
{
    addComp<CompType::POSITION>(
        PositionType(0, 0), SizeType(65, 71), true
    );
    addComp<CompType::ANIMATION>(
        "/home/wlle/code/demo/sfml2/resource/plant/PeaShooter/"
        "Peashooter.png"
    );
    getComp<CompType::ANIMATION>()->setAnimationPos({0, 0});
}