#include <animation/gamescene.hpp>
#include <entity/background.hpp>
#include <entity/plant/factory.hpp>
#include <entity/tool/plant_creator.hpp>
#include <event_manager.hpp>
#include <UI/defines.hpp>

using namespace std;
using namespace sf;
using namespace demo;

static const string CARD_PATH{
    "/home/wlle/sfml2/resource/background/Card.png"
};

PlantCreator::PlantCreator() :
    Tool("PlantCreator"), m_background(make_unique<Background>())
{
}

bool validPlantPosition(const Vector2i& pos)
{
    auto offset =
        pos
        - Vector2i(
            UI_DEFINE::GRASS_START_X, UI_DEFINE::GRASS_START_Y
        );
    return offset.x >= 0
           && offset.x
                  < UI_DEFINE::GRASS_LENGTH * UI_DEFINE::GRASS_COUNT
           && offset.y >= 0
           && offset.y
                  < UI_DEFINE::GRASS_WIDE * UI_DEFINE::GRASS_PATH;
}

static const PositionType OFFSET(105, 10);
static const SizeType CARD_SIZE(70, 87);
static const SizeType ICON_SIZE = CARD_SIZE - SizeType(20, 20);

void PlantCreator::init(std::string_view plant, int idx)
{
    PositionType position = UI_DEFINE::SHOP_POSITION + OFFSET
                            + SizeType(idx * CARD_SIZE.x, 0);
    m_background->init(CARD_PATH, position, CARD_SIZE);
    auto certerPos =
        m_background->getComp<CompType::POSITION>()->getCenterPos();

    m_plant = string(plant);
    _initComps(position, ICON_SIZE);
    _initEvents();

    getComp<CompType::POSITION>()->setCenterPosition(certerPos);
}

void PlantCreator::use(const Vector2i& pos)
{
    if(!validPlantPosition(pos)) {
        return;
    }
    auto newPlant = PlantFactory::getFactory()->create(m_plant, pos);
    getScene()->addPlant(newPlant);
    if(auto animation = getComp<CompType::ANIMATION>(); animation) {
        animation->resetColor();
    }
}

void PlantCreator::_initComps(
    const PositionType& position, const SizeType& size
)
{
    addComp<CompType::POSITION>(
        RangeType::Rectangle, position, size, true
    );
    // TODO: 根据plant找
    addComp<CompType::ANIMATION>(
        "/home/wlle/code/demo/sfml2/resource/plant/" + m_plant + '/'
        + m_plant + ".png"
    );
    getComp<CompType::ANIMATION>()->setAnimationPos(position);
    getComp<CompType::ANIMATION>()->setSize(size);
}

void PlantCreator::_initEvents()
{
    registerEvent(
        this,
        EventType::Click,
        [](Entity* entity, const std::any&) {
            if(auto animation =
                   entity->getComp<CompType::ANIMATION>();
               animation) {
                animation->setColor(sf::Color(255, 255, 255, 100));
            }
        }
    );
}

void PlantCreator::update()
{
    // 丑陋的写法，只是为了兼容
    // 一个Entity里塞入其他Entity就会有这么多问题 •_ゝ•
    if(m_background->getScene() == nullptr) {
        m_background->setScene(getScene());
    }
    m_background->update();
    Tool::update();
}