#include <entity/tool/tool.hpp>

namespace demo {

class PlantCreator : public Tool
{
public:
    explicit PlantCreator(const std::string& plant) : m_plant(plant)
    {
        _initComp();
    }
    ~PlantCreator() = default;

    void click(const sf::Vector2i& pos) override;
    void setPlant(const std::string&);

private:
    void _initComp();

private:
    std::string m_plant;
};

} // namespace demo