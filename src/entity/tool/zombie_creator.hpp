#pragma once

#include <components/cd.hpp>
#include <entity/tool/tool.hpp>

namespace demo {

class ZombieCreator : public Tool
{
public:
    ZombieCreator() : Tool("ZombieCreator")
    {
    }

    void setCD(int cd)
    {
        m_cd.setCD(cd);
    }

    void update() override;

protected:
    void _statusFunction()
    {
    }

private:
    bool _validCreate() const;
    void _createZombie(const std::string&, int);
    CD m_cd;
};

} // namespace demo