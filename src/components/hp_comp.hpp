#pragma once

#include <components/component.hpp>

namespace demo {

class HPComp : public Component
{
public:
    explicit HPComp(float hp) : m_HP(hp)
    {
    }
    ~HPComp() = default;
    void downHP(float);
    float getHP() const
    {
        return m_HP;
    }
    bool isDied() const
    {
        return getHP() <= 0;
    }

    void update(Entity*) override;

private:
    float m_HP;
};

} // namespace demo