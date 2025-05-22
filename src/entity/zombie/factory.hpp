#include <entity/zombie/zombie.hpp>

#include <memory>

namespace demo {

class ZombieFactory
{
public:
    ~ZombieFactory() = default;

    Zombie* create(const std::string& name, int path);

    static ZombieFactory* getFactory()
    {
        static ZombieFactory factory;
        return &factory;
    }

private:
    explicit ZombieFactory();

private:
    std::unordered_map<std::string, std::unique_ptr<ZombieData>>
        m_data;
};

} // namespace demo