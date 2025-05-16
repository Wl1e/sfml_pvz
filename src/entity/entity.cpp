#include <entity/components/animation_comp.hpp>
#include <entity/components/movement_comp.hpp>
#include <entity/components/position_comp.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

const Vector2i err_pos = {-1, -1};

void Entity::updade()
{
    // FIXME: 后续将计算分离出去，只有animation才在主线程更新
    for(auto& it : m_component) {
        it.second->update(this);
    }
}
