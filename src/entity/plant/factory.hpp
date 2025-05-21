#include <entity/plant/plant.hpp>

#include <memory>

namespace demo {

class PlantFactory
{
public:
    ~PlantFactory() = default;

    Plant* create(const std::string& name, const sf::Vector2i& pos);

    static PlantFactory* getFactory()
    {
        static PlantFactory factory;
        return &factory;
    }

private:
    PlantFactory();

private:
    std::unordered_map<std::string, std::unique_ptr<PlantData>>
        m_data;
};

} // namespace demo