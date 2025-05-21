#include <entity/entity.hpp>

namespace demo {

class spade : public Entity
{
    spade() : Entity(EntityType::TOOL)
    {
    }

    void use();

protected:
    void _statusFunction() override;
};

} // namespace demo