#include <entity/tool/tool.hpp>

namespace demo {

class Background;

class PlantCreator : public Tool
{
public:
    explicit PlantCreator();
    ~PlantCreator() = default;

    void init(std::string_view, int idx);
    void use(const sf::Vector2i& pos) override;
    void update() override;

private:
    void _initComps(const PositionType&, const SizeType&);
    void _initEvents();

private:
    std::string m_plant;

    std::unique_ptr<Background> m_background;
};

} // namespace demo