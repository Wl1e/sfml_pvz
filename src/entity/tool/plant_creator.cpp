#include <animation/gamescene.hpp>
#include <entity/plant/factory.hpp>
#include <entity/tool/plant_creator.hpp>

using namespace std;
using namespace sf;
using namespace demo;

PlantCreator::PlantCreator(const std::string& plant) :
    Tool("PlantCreator"), m_plant(plant)
{
    _initComps();
    _initEvents();
}

void PlantCreator::use(const Vector2i& pos)
{
    auto newPlant = PlantFactory::getFactory()->create(m_plant, pos);
    getScene()->addPlant(newPlant);
}

void PlantCreator::_initComps()
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

void PlantCreator::_initEvents()
{
}