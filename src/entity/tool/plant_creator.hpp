#include <entity/tool/tool.hpp>

namespace demo {

class PlantCreator : public Tool
{
public:
    explicit PlantCreator(const std::string&);
    ~PlantCreator() = default;

    void setPlant(const std::string& plant)
    {
        m_plant = plant;
    }
    void use(const sf::Vector2i& pos) override;

private:
    void _initComps();
    void _initEvents();

private:
    std::string m_plant;
};

} // namespace demo