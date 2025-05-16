#include <entity/components/attack_comp.hpp>

using namespace std;
using namespace sf;
using namespace demo;

static const int MIN_RANGE = -10;
static const int MAX_RANGE = 1000;

AttackComp::AttackComp(int damage, const Vector2i& range, int cd) :
    m_damage(damage), m_range(range), m_cd(cd)
{
    if(m_range.x < MIN_RANGE) {
        m_range.x = MIN_RANGE;
    }
    if(m_range.y > MAX_RANGE) {
        m_range.y = MAX_RANGE;
    }
}