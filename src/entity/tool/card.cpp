#include <entity/background.hpp>
#include <entity/tool/card.hpp>
#include <entity/tool/plant_creator.hpp>

using namespace std;
using namespace demo;

static const string CARD_PATH{
    "/home/wlle/sfml2/resource/background/Card.png"
};

Card::Card(
    std::string_view plant,
    const PositionType& position,
    const SizeType& size
) :
    Tool("Card"), m_background(make_unique<Background>()),
    m_plantCreator(make_unique<PlantCreator>())
{
    _initComps(plant, position, size);
    _initEvents();
}

void Card::_initComps(
    std::string_view plant,
    const PositionType& position,
    const SizeType& size
)
{
    m_background->init(CARD_PATH, position, size);
    m_plantCreator->init(plant, position, size);
}
void Card::_initEvents()
{
}

void Card::update()
{
    // 丑陋的写法，只是为了兼容
    // 一个Entity里塞入其他Entity就会有这么多问题 •_ゝ•
    if(m_background->getScene() == nullptr) {
        m_background->setScene(getScene());
    }
    if(m_plantCreator->getScene() == nullptr) {
        m_plantCreator->setScene(getScene());
    }
    m_background->update();
    m_plantCreator->update();
}

void Card::use(const sf::Vector2i& pos)
{
    printf("use\n");
    m_plantCreator->use(pos);
}