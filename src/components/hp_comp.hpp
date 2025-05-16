#pragma once

#include <components/component.hpp>

namespace demo {

class HPComp : public Component
{
public:
    HPComp(int hp) : m_HP(hp)
    {
    }
    ~HPComp() = default;
    void downHP(int value)
    {
        m_HP -= value;
    }
    int getHP() const
    {
        return m_HP;
    }
    bool isDied() const
    {
        return getHP() <= 0;
    }

    void update(Entity*) override
    {
        // FIXME: 更新实体状态
    }

private:
    int m_HP;
};

} // namespace demo