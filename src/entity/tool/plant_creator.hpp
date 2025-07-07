#include <entity/tool/tool.hpp>

namespace demo {

class PlantCreator : public Tool
{
public:
    explicit PlantCreator();
    ~PlantCreator() = default;

    void
    init(std::string_view, const PositionType&, const SizeType&);
    void use(const sf::Vector2i& pos) override;

private:
    void _initComps(const PositionType&, const SizeType&);
    void _initEvents();

private:
    std::string m_plant;
};

} // namespace demo