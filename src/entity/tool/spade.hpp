#include <entity/tool/tool.hpp>

#include <animation/gamescene.hpp>

namespace demo {

// class SpadeHandler : public HandTool
// {
// public:
//     SpadeHandler() = default;
//     ~SpadeHandler() = default;

//     void use(const sf::Vector2i& pos)
//     {
//         getScene()->delPlant(pos2axis(PositionType(pos)));
//     }

// protected:
//     void _statusFunction() override;
// };

class Spade : public Tool
{
    Spade() = default;
    ~Spade() = default;

    void click(const sf::Vector2i& pos) override
    {
    }

protected:
    void _statusFunction() override
    {
    }
};

} // namespace demo