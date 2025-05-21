#include <entity/plant/plant.hpp>

namespace demo {

class PlantFactory
{
public:
    ~PlantFactory() = default;

    Plant* create(std::string_view name);

    static PlantFactory* getFactory()
    {
        static PlantFactory factory;
        return &factory;
    }

private:
    PlantFactory();

private:
    std::unordered_map<std::string, PlantData*> m_data;
};

} // namespace demo