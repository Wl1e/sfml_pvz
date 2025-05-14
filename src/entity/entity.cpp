#include <entity/components/animation_comp.hpp>
#include <entity/components/position_comp.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

const sf::Vector2i& Entity::getPos()
{
    // if(!m_component.count(CompType::POSITION)) {
    //     return {-1, -1};
    // }

    // fixme: 有的是PositionComp，有的是AxisPositionComp
    auto& posComp = m_component.at(CompType::POSITION);
    auto p = dynamic_cast<PositionComp*>(
        m_component.at(CompType::POSITION).get()
    );
    return p->getPos();
}

void Entity::updade()
{
    // fixme: 后续将计算分离出去，只有animation才在主线程更新
    for(auto& it : m_component) {
        it.second->update();
    }
}

// template<CompType type, typename... Args>
// void Entity::addComp(Args&&... args)
// {
//     // fixme
//     if(type == CompType::POSITION) {
//         m_component[type] =
//             std::make_unique<PositionComp>(std::forward<Args>(args
//             )...);
//     } else if(type == CompType::AXIS_POSITION) {
//         m_component[type] = std::make_unique<AxisPositionComp>(
//             std::forward<Args>(args)...
//         );
//     } else if(type == CompType::ANIMATION) {
//         m_component[type] =
//             std::make_unique<AnimationComp>(std::forward<Args>(args
//             )...);
//     }
//     m_component[type]->whenAdded(this);
// }
