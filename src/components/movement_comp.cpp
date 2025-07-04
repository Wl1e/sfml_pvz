#include <components/position_comp.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void MovementComp::update(Entity* entity)
{
    if(m_distance <= 0) {
        entity->updateStatus(EntityStatus::Death);
        return;
    }
    // 加减速
    if(m_acceleration != 0) {
        if(m_acceleration > 0 && m_speed < m_max_speed) {
            m_speed =
                std::min(m_speed + m_acceleration, m_max_speed);
        } else if(m_acceleration < 0 && m_speed > m_max_speed) {
            m_speed =
                std::max(m_speed + m_acceleration, m_max_speed);
        }
    }
    m_distance -= m_speed;
}